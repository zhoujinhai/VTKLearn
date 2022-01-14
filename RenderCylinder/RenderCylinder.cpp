#include "vtkRenderWindow.h"
#include "vtkSmartPointer.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkCylinderSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkJPEGReader.h"
#include "vtkTexture.h"


int main(){
	// 派生自vtkPolyDataAlgorithm， 生成一个中心在渲染场景原点的柱体，长轴沿着Y轴
	vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
	cylinder->SetHeight(3.0);         // 设置柱体高度 
	cylinder->SetRadius(1.0);         // 设置柱体横截面半径
	cylinder->SetResolution(10);      // 设置柱体横截面的等边多边形的边数
	
	// 派生自vtkMapper 渲染多边形几何数据, 将输入的数据转换为几何图元（点、线、多边形）进行渲染
	vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cylinderMapper->SetInputConnection(cylinder->GetOutputPort());   // VTK可视化管线的输入数据接口

	// 加入文理贴图
	vtkSmartPointer<vtkJPEGReader> jpegReader = vtkSmartPointer<vtkJPEGReader>::New();
	jpegReader->SetFileName("./texture1.jpg");
	vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
	texture->SetInputConnection(jpegReader->GetOutputPort());
	texture->InterpolateOn();

	// 派生自vtkProp, 负责渲染场景中数据的可视化（位置 大小及方向信息）， 3维空间离常用vtkActor(几何数据)， vtkVolume(体数据)， 2维空间用vtkActor2D
	// 依赖于vtkMapper(负责存放数据和渲染信息) 和 vtkProperty(负责控制颜色、透明度等参数)
	vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
	cylinderActor->SetMapper(cylinderMapper);
	cylinderActor->SetTexture(texture);
	
	//// 方式一 设置property属性 
	//cylinderActor->GetProperty()->SetColor(1.0, 0.0, 0.0);   // 设置property属性
	//// 方式二 设置property属性
	//vtkSmartPointer<vtkProperty> cylinderProperty = vtkSmartPointer<vtkProperty>::New();
	//cylinderProperty->SetColor(1.0, 0.0, 0.0);
	//cylinderActor->SetProperty(cylinderProperty);

	
	// 负责管理场景的渲染过程，组成场景中所有对象 包括Prop, Camera, Light等
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(cylinderActor);
	renderer->SetBackground(0.1, 0.2, 0.4);  // SetBackground2()用于设置渐变色，需要先打开SetGradientBackground(bool)
	
	// 将操作系统与VTK渲染连接到一起
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(renderer);
	renWin->SetSize(300, 300);  // 窗口大小 像素为单位
	
	// 提供平台独立的响应鼠标 键盘 和 时钟事件的交互机制
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);  // 设置渲染窗口
	
	// 交互器样式的一种
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	iren->SetInteractorStyle(style);  // 定义交互器样式
	 
	iren->Initialize();               // 为处理窗口事件做准备
	iren->Start();                    // 开始进入事件响应循环
	
	std::cin.get();
	return 0;
}