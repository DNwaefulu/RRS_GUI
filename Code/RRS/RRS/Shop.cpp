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
void BC_main_menu(Fl_Widget*, void*);
void PB_main_menu(Fl_Widget*, void*);
void SA_main_menu(Fl_Widget*, void*);

void close_window(Fl_Widget* window, void*);

//first_window
Fl_Window *main_logon = new Fl_Window(w_width, w_height, "Logon");

void select_user()
{
	Fl_Box *select_user = new Fl_Box(0, 0, 300, 75, "Please select user to login as");

	Fl_Button *PM = new Fl_Button(50, 75, 200, 50, "PM");
	Fl_Button *BC = new Fl_Button(50, 125, 200, 50, "BC");
	Fl_Button *PB = new Fl_Button(50, 175, 200, 50, "PB");
	Fl_Button *SA = new Fl_Button(50, 225, 200, 50, "SA");

	PM->callback(PM_main_menu, "PM");
	BC->callback(BC_main_menu, "BC");
	PB->callback(PB_main_menu, "PB");
	SA->callback(SA_main_menu, "SA");

	main_logon->end();
	main_logon->show();

	Fl::run();
}

void return_window(Fl_Widget* window, void*)
{
	((Fl_Window*)window)->hide();
	main_logon->show();
}

void PM_main_menu(Fl_Widget*, void*)
{
	main_logon->hide();

	Fl_Window *main_menu = new Fl_Window(w_width, w_height, "Project Manager Menu");
	
	main_menu->callback(return_window);

	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Logged in as: PM");
	
	Fl_Button *robot_model = new Fl_Button(50, 75, 200, 50, "Create Robot Model");
	Fl_Button *robot_parts = new Fl_Button(50, 150, 200, 50, "Create Robot Parts");

	main_menu->end();
	main_menu->show();

	Fl::run();
}

void BC_main_menu(Fl_Widget*, void*)
{
	main_logon->hide();

	Fl_Window *main_menu = new Fl_Window(w_width, w_height, "Beloved Customer Menu");
	
	main_menu->callback(return_window);

	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Logged in as: BC");

	Fl_Button *robot_model = new Fl_Button(50, 75, 200, 50, "Browse");

	main_menu->end();
	main_menu->show();

	Fl::run();
}

void PB_main_menu(Fl_Widget*, void*)
{
	main_logon->hide();

	Fl_Window *main_menu = new Fl_Window(w_width, w_height, "Pointy-Headed Boss Menu");
	
	main_menu->callback(return_window);

	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Logged in as: PB");

	Fl_Button *robot_model = new Fl_Button(50, 75, 200, 50, "Create New Customer");
	Fl_Button *robot_parts = new Fl_Button(50, 150, 200, 50, "Create New Sales Associate");

	main_menu->end();
	main_menu->show();

	Fl::run();
}

void SA_main_menu(Fl_Widget*, void*)
{
	main_logon->hide();

	Fl_Window *main_menu = new Fl_Window(w_width, w_height, "Sales Associate Menu");
	
	main_menu->callback(return_window);
	
	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Logged in as: SA");

	Fl_Button *robot_model = new Fl_Button(50, 75, 200, 50, "Create Order");
	
	main_menu->end();
	main_menu->show();

	Fl::run();
}

int main() 
{
	select_user();

	return 0;
}

