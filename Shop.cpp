#include<stdlib.h>
#include<FL/Fl.H>
#include<FL/Fl_Box.H>
#include<FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H> 
#include <FL/Fl_Button.H> 

//to have consistent window sizes
#define w_width 300
#define w_height 300

//prototypes
void select_user(); //selects user
void PM_main_menu(Fl_Widget*, void*); //displays menu for selected user

//first_window
Fl_Window *main_logon = new Fl_Window(w_width, w_height, "Robbie Robot Shop - Logon");

void select_user()
{
	Fl_Box *select_user = new Fl_Box(0, 0, 300, 75, "Please select user");

	Fl_Button *PM = new Fl_Button(50, 75, 200, 50, "PM");
	Fl_Button *BC = new Fl_Button(50, 125, 200, 50, "BC");
	Fl_Button *PB = new Fl_Button(50, 175, 200, 50, "PB");
	Fl_Button *SA = new Fl_Button(50, 225, 200, 50, "SA");

	PM->callback(PM_main_menu, "PM");
	//BC->callback(main_menu, "BC");
	//PB->callback(main_menu, "PB");
	//SA->callback(main_menu, "SA");

	main_logon->end();
	main_logon->show();

	Fl::run();
}

void PM_main_menu(Fl_Widget*, void*)
{
	main_logon->hide();

	Fl_Window *main_menu = new Fl_Window(w_width, w_height, "Project Manager Menu");
	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Logged in as: PM");
	
	Fl_Button *robot_model = new Fl_Button(50, 75, 200, 50, "Create Robot Model");
	Fl_Button *robot_parts = new Fl_Button(50, 150, 200, 50, "Create Robot Parts");

	main_menu->end();
	main_menu->show();

	Fl::run();
}

int main() 
{
	select_user();

	return 0;
}

