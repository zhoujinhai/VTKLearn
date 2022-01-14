#include "vtkRenderWindow.h"
#include "vtkSmartPointer.h"
#include "vtkStructuredPointsReader.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkMarchingCubes.h"
#include "vtkRenderer.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"


int main(int argc, char* argv[])
{
	//读入Structured_Points类型的vtk文件。
	vtkSmartPointer<vtkStructuredPointsReader> reader = vtkSmartPointer<vtkStructuredPointsReader>::New();
	reader->SetFileName("./head.vtk");
	
	//用移动立方体法提取等值面。
	vtkSmartPointer<vtkMarchingCubes> marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
	marchingCubes->SetInputConnection(reader->GetOutputPort());
	marchingCubes->SetValue(0, 500);  ////显示皮肤  // SetValue(0, 1150);  //显示骨骼
	
	//将生成的等值面数据进行Mapper
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(marchingCubes->GetOutputPort());
	
	//把Mapper的输出送入渲染引擎进行显示
	//渲染引擎部分
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	renWin->AddRenderer(renderer);
	interactor->SetRenderWindow(renWin);

	renderer->AddActor(actor);
	renderer->Render();

	interactor->Initialize();
	interactor->Start();
	
	std::cin.get();
	return 0;
}