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
void select_user();

//PM Menu
void PM_main_menu(Fl_Widget*, void*); 
//	Choose Between RobotParts and RobotModels
void create_robot_parts(Fl_Widget*, void*);
void robot_parts_menu_closed(Fl_Widget* window, void*);

//		Create Torso
void create_torso(Fl_Widget*, void*);
void torso_name_next_cb(Fl_Widget*, void*);
void torso_name_input_cb(Fl_Widget* text, void*);
void torso_weight_input_cb(Fl_Widget* text, void*);
void torso_weight_next_cb(Fl_Widget*, void*);
void torso_cost_input_cb(Fl_Widget* text, void*);
void torso_cost_next_cb(Fl_Widget*, void*);
void torso_description_input_cb(Fl_Widget* text, void*);
void torso_description_next_cb(Fl_Widget*, void*);
void torso_battery_input_cb(Fl_Widget*, void* number);
void torso_submit(Fl_Widget*, void*);
//		Create Locomotor
void create_locomotor(Fl_Widget*, void*);
void loco_name_next_cb(Fl_Widget*, void*);
void loco_name_input_cb(Fl_Widget* text, void*);
void loco_weight_input_cb(Fl_Widget* text, void*);
void loco_weight_next_cb(Fl_Widget*, void*);
void loco_cost_input_cb(Fl_Widget* text, void*);
void loco_cost_next_cb(Fl_Widget*, void*);
void loco_description_input_cb(Fl_Widget* text, void*);
void loco_description_next_cb(Fl_Widget*, void*);
void loco_submit(Fl_Widget*, void*);
void loco_max_speed_input_cb(Fl_Widget* text, void*);
void loco_max_speed_next_cb(Fl_Widget*, void*);
void loco_power_consumed_input_cb(Fl_Widget* number, void*);

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
	RobotPart()
	{

	}

	const char* get_name();
	const char* get_part_number();
	const char* get_type();
	double get_weight();
	double get_cost();
	const char* get_description();
protected:
	const char* name;
	int part_number;
	const char* type;
	double weight;
	double cost;
	const char* description;
};

int g_part_number = 0;

const char* torso_name;
double torso_weight;
double torso_cost;
const char* torso_description;
int torso_battery_components = 1;

class Torso : public RobotPart
{
public:
	Torso(const char* p_name, const char* p_description, double p_weight, double p_cost, int p_batteries)
	{
		name = p_name;
		part_number = ++g_part_number;
		type = "Torso";
		weight = p_weight;
		cost = p_cost;
		battery_components = p_batteries;
		printf("Torso Created!\n");
		printf(" name: %s\n part number: %d\n type: %s\n weight: %f\n cost: %f\n battery components: %d\n", name, part_number, type, weight, cost, battery_components);
	}

	int get_battery_components() { return battery_components; }
private:
	int battery_components;
};

vector<Torso> torsos;

const char* loco_name;
double loco_weight;
double loco_cost;
const char* loco_description;
double loco_max_speed;
double loco_power_consumed;

class Locomotor : public RobotPart
{
public:
	Locomotor(const char* p_name, const char* p_description, double p_weight, double p_cost, double p_speed, double p_power)
	{
		name = p_name;
		description = p_description;
		weight = p_weight;
		cost = p_cost;
		part_number = ++g_part_number;
		type = "Locomotor";
		max_speed = p_speed;
		power_consumed = p_power;
		printf("Locomotor Created!\n");
		printf(" name: %s\n part number: %d\n type: %s\n weight: %f\n cost: %f\n max speed: %f\n power consumed: %f\n", name, part_number, type, weight, cost, max_speed, power_consumed);
	}

	double get_max_speed() { return max_speed; }
	double get_power_cosumed() { return power_consumed; }

private:
	double max_speed;
	double power_consumed;
};

vector<Locomotor> locomotors;

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

void robot_parts_menu_closed(Fl_Widget* window, void*)
{
	pm_main_menu->show();
	((Fl_Window*)window)->hide();
}

Fl_Window* robot_parts_menu;

void parts_menu_closed(Fl_Widget* window, void*)
{
	robot_parts_menu->show();
	((Fl_Window*)window)->hide();
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
	locomotor->callback(create_locomotor);

	robot_parts_menu->end();
	robot_parts_menu->show();

	Fl::run();
}

/*-------------------------------Create Locomotor---------------------------------------------------*/

Fl_Window* loco_name_wizard;
void create_locomotor(Fl_Widget*, void*)
{
	robot_parts_menu->hide();
	loco_name_wizard = new Fl_Window(w_width, w_height, "Locomotor Name");
	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Enter Part Name");

	Fl_Button *next = new Fl_Button(200, 250, 50, 30, "Next");

	Fl_Input *name = new Fl_Input(50, 100, 200, 25, "");


	next->callback(loco_name_next_cb);
	name->callback(loco_name_input_cb);
	loco_name_wizard->callback(parts_menu_closed);

	loco_name_wizard->end();
	loco_name_wizard->show();
}

void loco_name_input_cb(Fl_Widget* text, void*)
{
	loco_name = ((Fl_Input*)text)->value();
	printf("Locomotor name submitted: %s\n", loco_name);
}

Fl_Window* loco_weight_wizard;

void loco_name_next_cb(Fl_Widget*, void*)
{
	loco_name_wizard->hide();

	loco_weight_wizard = new Fl_Window(w_width, w_height, "Locomotor Weight");
	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Enter Part Weight");
	Fl_Button *next = new Fl_Button(200, 250, 50, 30, "Next");
	Fl_Input *weight = new Fl_Input(50, 100, 200, 25, "");


	next->callback(loco_weight_next_cb);
	weight->callback(loco_weight_input_cb);
	loco_weight_wizard->callback(parts_menu_closed);

	loco_weight_wizard->end();
	loco_weight_wizard->show();
}

void loco_weight_input_cb(Fl_Widget* text, void*)
{
	const char* c_weight = ((Fl_Input*)text)->value();
	loco_weight = atof(c_weight);
	printf("Locomotor weight submitted: %f\n", loco_weight);
}

Fl_Window* loco_cost_wizard;
void loco_weight_next_cb(Fl_Widget*, void*)
{
	loco_weight_wizard->hide();

	loco_cost_wizard = new Fl_Window(w_width, w_height, "Locomotor Cost");
	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Enter Part Cost $");
	Fl_Button *next = new Fl_Button(200, 250, 50, 30, "Next");
	Fl_Input *cost = new Fl_Input(50, 100, 200, 25, "");

	next->callback(loco_cost_next_cb);
	cost->callback(loco_cost_input_cb);
	loco_cost_wizard->callback(parts_menu_closed);

	loco_cost_wizard->end();
	loco_cost_wizard->show();
}

void loco_cost_input_cb(Fl_Widget* text, void*)
{
	const char* c_cost = ((Fl_Input*)text)->value();
	loco_cost = atof(c_cost);
	printf("Locomotor cost submitted: %f\n", loco_cost);
}

Fl_Window* loco_description_wizard;
void loco_cost_next_cb(Fl_Widget*, void*)
{
	loco_cost_wizard->hide();

	loco_description_wizard = new Fl_Window(w_width, w_height, "Locomotor Description");
	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Enter Part Description");
	Fl_Button *next = new Fl_Button(200, 250, 50, 30, "Next");
	Fl_Input *description = new Fl_Input(50, 100, 200, 25, "");

	next->callback(loco_description_next_cb);
	description->callback(loco_description_input_cb);
	loco_description_wizard->callback(parts_menu_closed);

	loco_description_wizard->end();
	loco_description_wizard->show();
}

void loco_description_input_cb(Fl_Widget* text, void*)
{
	loco_description = ((Fl_Input*)text)->value();
	printf("Locomotor description submitted: %s\n", loco_description);
}

Fl_Window* loco_max_speed_wizard;
void loco_description_next_cb(Fl_Widget*, void*)
{
	loco_description_wizard->hide();

	loco_max_speed_wizard = new Fl_Window(w_width, w_height, "Locomotor Max Speed");
	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Input Max Speed");
	Fl_Button *next = new Fl_Button(200, 250, 50, 30, "Next");
	Fl_Input* speed = new Fl_Input(50, 100, 200, 25, "");


	next->callback(loco_max_speed_next_cb);
	speed->callback(loco_max_speed_input_cb);

	loco_max_speed_wizard->callback(parts_menu_closed);

	loco_max_speed_wizard->end();
	loco_max_speed_wizard->show();
}

void loco_max_speed_input_cb(Fl_Widget* text, void*)
{
	const char* c_speed = ((Fl_Input*)text)->value();
	loco_max_speed = atof(c_speed);
	printf("max speed: %f", loco_max_speed);
}


Fl_Window* loco_power_consumed_wizard;
void loco_max_speed_next_cb(Fl_Widget*, void*)
{
	loco_max_speed_wizard->hide();


	loco_power_consumed_wizard = new Fl_Window(w_width, w_height, "Locomotor Power Consumed");
	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Input Power Consumed");
	Fl_Button *submit = new Fl_Button(200, 250, 50, 30, "Submit");
	Fl_Input* speed = new Fl_Input(50, 100, 200, 25, "");

	submit->callback(loco_submit);
	speed->callback(loco_power_consumed_input_cb);

	loco_power_consumed_wizard->callback(parts_menu_closed);

	loco_power_consumed_wizard->end();
	loco_power_consumed_wizard->show();
}

void loco_power_consumed_input_cb(Fl_Widget* number, void*)
{
	const char* c_power_consumed = ((Fl_Input*)number)->value();
	loco_power_consumed = atof(c_power_consumed);
	printf("Loco power consumed submitted: %d\n", loco_power_consumed);
}

void loco_submit(Fl_Widget*, void*)
{
	Locomotor loco(loco_name, loco_description, loco_weight, loco_cost, loco_max_speed, loco_power_consumed);
	loco_power_consumed_wizard->hide();
	robot_parts_menu->show();
	locomotors.push_back(loco);
	printf("Locomotor added to loco vector\n");
}

/*-------------------------------------Create Torso--------------------------------------------------*/

Fl_Window* torso_name_wizard;
void create_torso(Fl_Widget*, void*)
{
	robot_parts_menu->hide();
	torso_name_wizard = new Fl_Window(w_width, w_height, "Torso Name");
	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Enter Part Name");

	Fl_Button *next = new Fl_Button(200, 250, 50, 30, "Next");

	Fl_Input *name = new Fl_Input(50, 100, 200, 25, "");


	next->callback(torso_name_next_cb);
	name->callback(torso_name_input_cb);
	torso_name_wizard->callback(parts_menu_closed);

	torso_name_wizard->end();
	torso_name_wizard->show();
}

void torso_name_input_cb(Fl_Widget* text, void*)
{
	torso_name = ((Fl_Input*)text)->value();
	printf("Torso name submitted: %s\n", torso_name);
}

Fl_Window* torso_weight_wizard;

void torso_name_next_cb(Fl_Widget*, void*)
{
	torso_name_wizard->hide();
	
	torso_weight_wizard = new Fl_Window(w_width, w_height, "Torso Weight");
	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Enter Part Weight");
	Fl_Button *next = new Fl_Button(200, 250, 50, 30, "Next");
	Fl_Input *weight = new Fl_Input(50, 100, 200, 25, "");

	
	next->callback(torso_weight_next_cb);
	weight->callback(torso_weight_input_cb);
	torso_weight_wizard->callback(parts_menu_closed);

	torso_weight_wizard->end();
	torso_weight_wizard->show();
}

void torso_weight_input_cb(Fl_Widget* text, void*)
{
	const char* c_weight = ((Fl_Input*)text)->value();
	torso_weight = atof(c_weight);
	printf("Torso weight submitted: %f\n", torso_weight);
}

Fl_Window* torso_cost_wizard;
void torso_weight_next_cb(Fl_Widget*, void*)
{
	torso_weight_wizard->hide();

	torso_cost_wizard = new Fl_Window(w_width, w_height, "Torso Cost");
	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Enter Part Cost $");
	Fl_Button *next = new Fl_Button(200, 250, 50, 30, "Next");
	Fl_Input *cost = new Fl_Input(50, 100, 200, 25, "");

	next->callback(torso_cost_next_cb);
	cost->callback(torso_cost_input_cb);
	torso_cost_wizard->callback(parts_menu_closed);

	torso_cost_wizard->end();
	torso_cost_wizard->show();
}

void torso_cost_input_cb(Fl_Widget* text, void*)
{
	const char* c_cost = ((Fl_Input*)text)->value();
	torso_cost = atof(c_cost);
	printf("Torso cost submitted: %f\n", torso_cost);
}

Fl_Window* torso_description_wizard;
void torso_cost_next_cb(Fl_Widget*, void*)
{
	torso_cost_wizard->hide();

	torso_description_wizard = new Fl_Window(w_width, w_height, "Torso Description");
	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Enter Part Description");
	Fl_Button *next = new Fl_Button(200, 250, 50, 30, "Next");
	Fl_Input *description = new Fl_Input(50, 100, 200, 25, "");

	next->callback(torso_description_next_cb);
	description->callback(torso_description_input_cb);
	torso_cost_wizard->callback(parts_menu_closed);

	torso_description_wizard->end();
	torso_description_wizard->show();
}

void torso_description_input_cb(Fl_Widget* text, void*)
{
	torso_description = ((Fl_Input*)text)->value();
	printf("Torso description submitted: %s\n", torso_description);
}

Fl_Window* torso_battery_wizard;
void torso_description_next_cb(Fl_Widget*, void*)
{
	torso_description_wizard->hide();

	torso_battery_wizard = new Fl_Window(w_width, w_height, "Torso Batteries");
	Fl_Box *text = new Fl_Box(0, 0, 300, 75, "Select How Many Batteries");
	Fl_Button *submit = new Fl_Button(200, 250, 50, 30, "Submit");
	Fl_Button *one = new Fl_Button(125, 100, 50, 30, "1");
	Fl_Button *two = new Fl_Button(125, 150, 50, 30, "2");
	Fl_Button *three = new Fl_Button(125, 200, 50, 30, "3");

	submit->callback(torso_submit);

	one->callback(torso_battery_input_cb, "1");
	two->callback(torso_battery_input_cb, "2");
	three->callback(torso_battery_input_cb, "3");

	torso_cost_wizard->callback(parts_menu_closed);
	
	torso_battery_wizard->end();
	torso_battery_wizard->show();
}

void torso_battery_input_cb(Fl_Widget*, void* number)
{
	const char* c_batteries = ((const char*)number);
	torso_battery_components = atoi(c_batteries);
	printf("Torso battery components submitted: %d\n", torso_battery_components);
}

void torso_submit(Fl_Widget*, void*)
{
	Torso torso(torso_name, torso_description, torso_weight, torso_cost, torso_battery_components);
	torso_battery_wizard->hide();
	robot_parts_menu->show();
	torsos.push_back(torso);
	printf("torso added to torso vector\n");
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