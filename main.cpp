#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum object_type
{
    HOUSE,
    GARAGE,
    BARN,
    BATH_HOUSE,
    UNDEFINED_OBJECT
};

enum room_type
{
    KITCHEN,
    BATHROOM,
    BEDROOM,
    CHILD_ROOM,
    LIVING_ROOM,
    UNDEFINED_ROOM
};

struct room_info
{
    room_type type;
    float area;
};

struct floor_info
{
    float height = 0;
    int room_count;

    vector<room_info> room;
};

struct building_info
{
    enum object_type object_type;
    float area = 0;
    int floor_count;
    bool furnace = false;

    vector<floor_info> floor;
};

struct plot_info
{
    int number;
    int building_count;

    vector<building_info> building;
};

void room_type_str_to_enum (string& room_type_str, room_info* room_info)
{
    if (room_type_str == "kitchen")
        room_info->type = KITCHEN;
    else if (room_type_str == "bathroom")
        room_info->type = BATHROOM;
    else if (room_type_str == "bedroom")
        room_info->type = BEDROOM;
    else if (room_type_str == "children`s room")
        room_info->type = CHILD_ROOM;
    else if (room_type_str == "living room")
        room_info->type = LIVING_ROOM;
    else
        room_info->type = UNDEFINED_ROOM;
}

string room_type_converted (enum room_type n)
{
    if (n == KITCHEN)
        return "kitchen";
    else if (n == BATHROOM)
        return "bathroom";
    else if (n == BEDROOM)
        return "bedroom";
    else if (n == CHILD_ROOM)
        return "children`s room";
    else if (n == LIVING_ROOM)
        return "living room";
    else
        return "Incorrect data";
}

void building_type_str_to_enum (string& building_type_str, building_info* building_info)
{
    if (building_type_str == "house")
        building_info->object_type = HOUSE;
    else if (building_type_str == "garage")
        building_info->object_type = GARAGE;
    else if (building_type_str == "barn")
        building_info->object_type = BARN;
    else if (building_type_str == "bathhouse")
        building_info->object_type = BATH_HOUSE;
    else
        building_info->object_type = UNDEFINED_OBJECT;
}

string building_type_converted (enum object_type n)
{
    if (n == HOUSE)
        return "house";
    else if (n == GARAGE)
        return "garage";
    else if (n == BARN)
        return "barn";
    else if (n == BATH_HOUSE)
        return "bathhouse";
    else
        return "Incorrect data";
}

int main()
{
    int plot_count = 0;
    bool correct = false;

    cout << "Enter the number of plots: ";
    cin >> plot_count;

    vector<plot_info> village(plot_count);

    for (int i = 0; i < plot_count; ++i)
    {
        village[i].number = i + 1;

        //Enter plot data
        while (!correct)
        {
            cout << "Enter the number (1 - 4, House, Garage, Barn, Bathhouse) of buildings on the plot # " << village[i].number << endl;
            cin >> village[i].building_count;

            if (village[i].building_count >= 1 && village[i].building_count <= 4)
                correct = true;
            else
                cout << "Incorrect data!" << endl;
        }
        correct = false;

        village[i].building.resize(village[i].building_count);

        string building_type_str;

        for (int j = 0; j < village[i].building_count; ++j)
        {
            cout << "Enter building type (house, garage, barn, bathhouse) # " << j + 1 << endl;
            cin >> building_type_str;

            building_type_str_to_enum(building_type_str, &village[i].building[j]);

            cout << "Enter building area # " << j + 1 << endl;
            cin >> village[i].building[j].area;

            if (village[i].building[j].object_type == HOUSE || village[i].building[j].object_type == BATH_HOUSE)
            {
                cout << "In a construction there is a furnace with a pipe (1 - yes, 0 - no)? ";
                cin >> village[i].building[j].furnace;
            }

            if (village[i].building[j].object_type == HOUSE)
            {
                cout << "Enter more information about the house:" << endl;

                while (!correct)
                {
                    cout << "How many floors (1 - 3) in house?" << endl;
                    cin >> village[i].building[j].floor_count;

                    if (village[i].building[j].floor_count >= 1 && village[i].building[j].floor_count <= 3)
                        correct = true;
                    else
                        cout << "Incorrect data!" << endl;
                }
                correct = false;

                village[i].building[j].floor.resize(village[i].building[j].floor_count);

                cout << "Enter more information about the floors:" << endl;
                for (int k = 0; k < village[i].building[j].floor_count; ++k)
                {
                    cout << "Enter the height of the floor # " << k + 1 << endl;
                    cin >> village[i].building[j].floor[k].height;

                    while (!correct)
                    {
                        cout << "How many rooms (2 - 4) in the floor # " << k + 1 << endl;
                        cin >> village[i].building[j].floor[k].room_count;

                        if (village[i].building[j].floor[k].room_count >= 2 && village[i].building[j].floor[k].room_count <= 4)
                            correct = true;
                        else
                            cout << "Incorrect data." << endl;
                    }
                    correct = false;

                    village[i].building[j].floor[k].room.resize(village[i].building[j].floor[k].room_count);

                    cout << "Enter more information about the rooms:" << endl;

                    string room_type_str;
                    for (int l = 0; l < village[i].building[j].floor[k].room_count; ++l)
                    {
                        cout << "Enter the room type (kitchen, bathroom, bedroom, children`s room, living room) # " << l + 1 << endl;
                        cin >> room_type_str;

                        room_type_str_to_enum(room_type_str, &village[i].building[j].floor[k].room[l]);

                        cout << "Enter room area # " << l + 1 << " (" << room_type_converted(village[i].building[j].floor[k].room[l].type) << ")" << endl;
                        cin >> village[i].building[j].floor[k].room[l].area;
                    }
                }
            }
        }
    }

    //Plots data output
    for (int i = 0; i < plot_count; ++i)
    {
        cout << "Plot # " << village[i].number << endl;

        //Buildings
        for (int j = 0; j < village[i].building_count; ++j)
        {
            cout << " " << building_type_converted(village[i].building[j].object_type) << " area: " << village[i].building[j].area << endl;
            if (village[i].building[j].furnace)
            {
                cout << " There is a stove witch chimney" << endl;
            }
            cout << " Number of floors - " << village[i].building[j].floor_count << endl;

            //Floors
            for (int k = 0; k < village[i].building[j].floor_count; ++k)
            {
                cout << "    Floor # " << k + 1 << " height - " << village[i].building[j].floor[k].height << endl;
                cout << "    Numbers of rooms per floor - " << village[i].building[j].floor[k].room_count << endl;

                //Rooms
                for (int l = 0; l < village[i].building[j].floor[k].room_count; ++l)
                {
                    cout << "       " << room_type_converted(village[i].building[j].floor[k].room[l].type) << endl;
                    cout << "      Area - " << village[i].building[j].floor[k].room[l].area << endl;
                }
            }
        }
        cout << "--------------------------------------" << endl;
    }

    cout << "Numbers of buildings in the village - " << endl;
    int building_sum = 0;
    for (int i = 0; i < plot_count; ++i)
    {
        building_sum += village[i].building_count;
    }
    cout << building_sum;
}