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
	// ������vtkPolyDataAlgorithm�� ����һ����������Ⱦ����ԭ������壬��������Y��
	vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
	cylinder->SetHeight(3.0);         // ��������߶� 
	cylinder->SetRadius(1.0);         // ������������뾶
	cylinder->SetResolution(10);      // ������������ĵȱ߶���εı���
	
	// ������vtkMapper ��Ⱦ����μ�������, �����������ת��Ϊ����ͼԪ���㡢�ߡ�����Σ�������Ⱦ
	vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cylinderMapper->SetInputConnection(cylinder->GetOutputPort());   // VTK���ӻ����ߵ��������ݽӿ�

	// ����������ͼ
	vtkSmartPointer<vtkJPEGReader> jpegReader = vtkSmartPointer<vtkJPEGReader>::New();
	jpegReader->SetFileName("./texture1.jpg");
	vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
	texture->SetInputConnection(jpegReader->GetOutputPort());
	texture->InterpolateOn();

	// ������vtkProp, ������Ⱦ���������ݵĿ��ӻ���λ�� ��С��������Ϣ���� 3ά�ռ��볣��vtkActor(��������)�� vtkVolume(������)�� 2ά�ռ���vtkActor2D
	// ������vtkMapper(���������ݺ���Ⱦ��Ϣ) �� vtkProperty(���������ɫ��͸���ȵȲ���)
	vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
	cylinderActor->SetMapper(cylinderMapper);
	cylinderActor->SetTexture(texture);
	
	//// ��ʽһ ����property���� 
	//cylinderActor->GetProperty()->SetColor(1.0, 0.0, 0.0);   // ����property����
	//// ��ʽ�� ����property����
	//vtkSmartPointer<vtkProperty> cylinderProperty = vtkSmartPointer<vtkProperty>::New();
	//cylinderProperty->SetColor(1.0, 0.0, 0.0);
	//cylinderActor->SetProperty(cylinderProperty);

	
	// �������������Ⱦ���̣���ɳ��������ж��� ����Prop, Camera, Light��
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(cylinderActor);
	renderer->SetBackground(0.1, 0.2, 0.4);  // SetBackground2()�������ý���ɫ����Ҫ�ȴ�SetGradientBackground(bool)
	
	// ������ϵͳ��VTK��Ⱦ���ӵ�һ��
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(renderer);
	renWin->SetSize(300, 300);  // ���ڴ�С ����Ϊ��λ
	
	// �ṩƽ̨��������Ӧ��� ���� �� ʱ���¼��Ľ�������
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);  // ������Ⱦ����
	
	// ��������ʽ��һ��
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	iren->SetInteractorStyle(style);  // ���彻������ʽ
	 
	iren->Initialize();               // Ϊ�������¼���׼��
	iren->Start();                    // ��ʼ�����¼���Ӧѭ��
	
	std::cin.get();
	return 0;
}