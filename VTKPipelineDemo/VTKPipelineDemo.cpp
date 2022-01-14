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
	//����Structured_Points���͵�vtk�ļ���
	vtkSmartPointer<vtkStructuredPointsReader> reader = vtkSmartPointer<vtkStructuredPointsReader>::New();
	reader->SetFileName("./head.vtk");
	
	//���ƶ������巨��ȡ��ֵ�档
	vtkSmartPointer<vtkMarchingCubes> marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
	marchingCubes->SetInputConnection(reader->GetOutputPort());
	marchingCubes->SetValue(0, 500);  ////��ʾƤ��  // SetValue(0, 1150);  //��ʾ����
	
	//�����ɵĵ�ֵ�����ݽ���Mapper
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(marchingCubes->GetOutputPort());
	
	//��Mapper�����������Ⱦ���������ʾ
	//��Ⱦ���沿��
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