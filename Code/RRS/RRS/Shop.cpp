#include<stdlib.h>
#include<FL/Fl.H>
#include<FL/Fl_Box.H>
#include<FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H> 
#include <FL/Fl_Button.H> 
#include <FL/Fl_Input.H>
#include <string>
#include <vector>

using namespace std;
//to have consistent window sizes
#define w_width 300
#define w_height 300

//prototypes
void select_user(); //selects user
void PM_main_menu(Fl_Widget*, void*); //displays menu for selected user
void create_robot_parts(Fl_Widget*, void*);
void robot_parts_menu_closed(Fl_Widget* window, void*);
void create_torso(Fl_Widget*, void*);
void create_robot_model(Fl_Widget*, void*);

void BC_main_menu(Fl_Widget*, void*);


void PB_main_menu(Fl_Widget*, void*);
void create_new_customer(Fl_Widget*, void*);
void create_new_sales_assoc(Fl_Widget*, void*);
void create_new_assoc_done(Fl_Widget*, void* text);
void assoc_done(Fl_Widget*, void*);
void create_new_customer_done(Fl_Widget*, void* text);
void customer_done(Fl_Widget*, void*);

void SA_main_menu(Fl_Widget*, void*);

void return_menu(Fl_Widget* window, void*);
void return_window(Fl_Window* window);

//first_window
Fl_Window *main_logon = new Fl_Window(w_width, w_height, "Logon");

class RobotPart {
public:
	RobotPart();

	const char* get_name();
	const char* get_part_number();
	const char* get_type();
	double get_weight();
	double get_cost();
	const char* get_description();
protected:
	const char* name;
	const char* part_number;
	const char* type;
	double weight;
	double cost;
	const char* description;
};

class Torso : public RobotPart
{
public:
	Torso();
	int get_battery_components() { return battery_components; }
private:
	int battery_components;
};

class Customer
{
public:
	Customer(const char* p_name) : name(p_name) {}
	const char* get_name() { return name; }
private:
	const char* name;
};

vector<Customer> customers;

class SalesAssoc
{
public:
	SalesAssoc(const char* p_name) : name(p_name) {}
	const char* get_name() { return name; }
private:
	const char* name;
};

vector<SalesAssoc> assocs;

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

void return_menu(Fl_Widget* window, void*)
{
	((Fl_Window*)window)->hide();
	main_logon->show();
}

Fl_Window* pm_main_menu;
void PM_main_menu(Fl_Widget*, void*)
{
	main_logon->hide();

	pm_main_menu = new Fl_Window(w_width, w_height, "Project Manager Menu");

	pm_main_menu->callback(return_menu);

	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Logged in as: PM");

	Fl_Button *robot_model = new Fl_Button(50, 75, 200, 50, "Create Robot Model");
	Fl_Button *robot_parts = new Fl_Button(50, 150, 200, 50, "Create Robot Parts");

	robot_parts->callback(create_robot_parts);
	robot_model->callback(create_robot_model);

	pm_main_menu->end();
	pm_main_menu->show();

	Fl::run();
}

void create_robot_model(Fl_Widget*, void*)
{
	pm_main_menu->hide();
	Fl_Window *create_menu = new Fl_Window(w_width, w_height, "Select Part Menu");

	Fl_Input *robot_name = new Fl_Input(140, 50, 150, 25, "Robot Model Name");

	create_menu->end();
	create_menu->show();

	Fl::run();
}

Fl_Window* robot_parts_menu;
void create_robot_parts(Fl_Widget* test, void*)
{
	pm_main_menu->hide();
	robot_parts_menu = new Fl_Window(w_width, w_height, "Select Part Menu");

	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Select Part to Create");

	Fl_Button *arm = new Fl_Button(50, 70, 200, 30, "Arm");
	Fl_Button *head = new Fl_Button(50, 110, 200, 30, "Head");
	Fl_Button *torso = new Fl_Button(50, 150, 200, 30, "Torso");
	Fl_Button *locomotor = new Fl_Button(50, 190, 200, 30, "Locomotor");
	Fl_Button *battery = new Fl_Button(50, 230, 200, 30, "Battery");
	
	robot_parts_menu->callback(robot_parts_menu_closed);
	
	torso->callback(create_torso);

	robot_parts_menu->end();
	robot_parts_menu->show();

	Fl::run();
}

void robot_parts_menu_closed(Fl_Widget* window, void*)
{
	pm_main_menu->show();
	((Fl_Window*)window)->hide();
}

Fl_Window* torso_name_wizard;

const char* torso_name;

void create_torso(Fl_Widget*, void*)
{
	robot_parts_menu->hide();
	torso_name_wizard = new Fl_Window(w_width, w_height, "Torso Name");
	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Enter Part Name");

	Fl_Button *next = new Fl_Button(200, 250, 50, 30, "Next");

	Fl_Input *name = new Fl_Input(50, 100, 200, 25, "");

	torso_name_wizard->end();
	torso_name_wizard->show();
}

void BC_main_menu(Fl_Widget*, void*)
{
	main_logon->hide();

	Fl_Window *main_menu = new Fl_Window(w_width, w_height, "Beloved Customer Menu");

	main_menu->callback(return_menu);

	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Logged in as: BC");

	Fl_Button *robot_model = new Fl_Button(50, 75, 200, 50, "Browse");

	main_menu->end();
	main_menu->show();

	Fl::run();
}

Fl_Window* pb_main_menu;
void PB_main_menu(Fl_Widget*, void*)
{
	main_logon->hide();

	Fl_Window *main_menu = new Fl_Window(w_width, w_height, "Pointy-Headed Boss Menu");
	pb_main_menu = main_menu;

	main_menu->callback(return_menu);

	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Logged in as: PB");

	Fl_Button *new_customer = new Fl_Button(50, 75, 200, 50, "Create New Customer");
	Fl_Button *new_sales_assoc = new Fl_Button(50, 150, 200, 50, "Create New Sales Associate");

	new_customer->callback(create_new_customer);
	new_sales_assoc->callback(create_new_sales_assoc);

	main_menu->end();
	main_menu->show();

	Fl::run();
}

void return_window(Fl_Window* window)
{
	window->show();
}

void pb_close_window(Fl_Widget* window, void*)
{
	((Fl_Window*)window)->hide();
	return_window(pb_main_menu);
}

Fl_Window* create_customer;
void create_new_customer(Fl_Widget*, void*)
{
	pb_main_menu->hide();

	create_customer = new Fl_Window(w_width, w_height, "Create Customer Menu");
	Fl_Input *customer_name = new Fl_Input(140, 50, 150, 25, "Customer Name");
	Fl_Button *done = new Fl_Button(225, 200, 50, 50, "Done");

	create_customer->callback(pb_close_window);

	customer_name->callback(create_new_customer_done);
	done->callback(customer_done);

	create_customer->end();
	create_customer->show();

	Fl::run();
}

void customer_done(Fl_Widget*, void*)
{
	create_customer->hide();
	pb_main_menu->show();

	int size = customers.size();

	printf("current customers: \n");
	for (int i = 0; i < size; i++)
	{
		printf("- %s\n", customers[i].get_name());
	}
}

void create_new_customer_done(Fl_Widget* text, void*)
{
	const char* name = ((Fl_Input*)text)->value();
	Customer customer(name);
	customers.push_back(customer);
	printf("Customer created: %s\n\n", name); //for debug
}

Fl_Window* create_sa;

void create_new_sales_assoc(Fl_Widget*, void*)
{
	pb_main_menu->hide();

	create_sa = new Fl_Window(w_width, w_height, "Create Associate Menu");
	Fl_Button *done = new Fl_Button(225, 200, 50, 50, "Done");
	Fl_Input *assoc_name = new Fl_Input(140, 50, 150, 25, "Associate Name");

	create_sa->callback(pb_close_window);

	assoc_name->callback(create_new_assoc_done);
	done->callback(assoc_done);

	create_sa->end();
	create_sa->show();

	Fl::run();
}

void assoc_done(Fl_Widget*, void*)
{
	create_sa->hide();
	pb_main_menu->show();

	int size = assocs.size();
	printf("current assocs: \n");
	for (int i = 0; i < size; i++)
	{
		printf("- %s\n", assocs[i].get_name());
	}
}

void create_new_assoc_done(Fl_Widget* text, void*)
{
	const char* name = ((Fl_Input*)text)->value();
	SalesAssoc assoc(name);
	assocs.push_back(assoc);
	printf("Assoc created: %s\n\n", name); //for debug
}

void SA_main_menu(Fl_Widget*, void*)
{
	main_logon->hide();

	Fl_Window *main_menu = new Fl_Window(w_width, w_height, "Sales Associate Menu");

	main_menu->callback(return_menu);

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