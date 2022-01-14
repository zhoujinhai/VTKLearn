#include "vtkRenderWindow.h"
#include "vtkSmartPointer.h"

int main(){
	// 智能指针定义一个窗口
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->Render();  // 显示并渲染窗口
	
	std::cin.get();
	return 0;
}