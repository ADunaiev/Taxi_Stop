#include <iostream>
#include <string.h>
#include <time.h>
#include <vector>
using namespace std;

//������� 2.
//������� ������������ ������ ���������� ����������
//�����.
// 
//���������� ������� ��������� ���������� :
// - ������� ����� ����� ����������� ���������� �� ���������
// � ������ ����� �����, 
// - ������� ����� ����� ����������� ��������� �� ��������� � ������ ����� �����, 
// - ��� ���������(�������� ��� ���).
// 
// ���������� ���������� : 
// - ������� ����� ���������� �������� �� ���������, 
// - ����������� �������� ������� ����� ��������� ���������, �����
//�� ��������� ���������� �� ����� N ����� ������������.
// 
// ���������� ��������� ���� � ��������� �������� ��������� ���������.

static const int number_of_day_intervals = 3;

class Day_Interval
{
    string name;
    int duration;  
public:
    Day_Interval();
    Day_Interval(string nameP, int durationP);
    string GetName() const;
    int GetDuration() const;
    void SetGetName(string napeP);
    void SetDuration(int durationP);
};

Day_Interval::Day_Interval(string nameP, int durationP) 
    : name{ nameP}, duration{ durationP }{}

Day_Interval::Day_Interval() : Day_Interval(nullptr, 0){}

string Day_Interval::GetName() const
{
    return name;
}
int Day_Interval::GetDuration() const
{
    return duration;
}
void Day_Interval::SetGetName(string nameP)
{
    name = nameP;
}
void Day_Interval::SetDuration(int durationP)
{
    duration = durationP;
}

class Queue
{
    //�������
    int* Wait;
    //������������ ������ �������
    const int MaxQueueLength = 1000;
    //������� ������ �������
    int QueueLength;
public:
    //�����������
    Queue();
    //����������
    ~Queue();
    //���������� ��������
    void Add(int c);
    //���������� ��������
    int Extract();
    //������� �������
    void Clear();
    //�������� ������������� ��������� � �������
    bool IsEmpty();
    //�������� �� ������������ �������
    bool IsFull();
    //���������� ��������� � �������
    int GetCount() const;
    int GetValue(int i) const;
    //������������ �������
    void Show();
    int Max_Element_Value() const;
};

void Queue::Show()
{
    cout << "-----------------------------------\n";
    //������������ �������
    for (int i = 0; i < QueueLength; i++)
    {
        cout << Wait[i] << " ";
    }
    cout << "\n-----------------------------------\n";
}
Queue::~Queue()
{
    //�������� �������
    delete[]Wait;
}
Queue::Queue()
{
    //������� �������
    Wait = new int[MaxQueueLength];
    //���������� ������� �����
    QueueLength = 0;
}
void Queue::Clear()
{
    //����������� "�������" �������
    QueueLength = 0;
}
bool Queue::IsEmpty()
{
    //����?
    return QueueLength == 0;
}
bool Queue::IsFull()
{
    //�����?
    return QueueLength == MaxQueueLength;
}
int Queue::GetCount() const
{
    //���������� �������������� � ����� ���������
    return QueueLength;
}
int Queue::GetValue(int i) const
{
    return Wait[i];
}
void Queue::Add(int c)
{
    //���� � ������� ���� ��������� �����,
    //�� ����������� ����������
    //�������� � ��������� ����� �������
    if (!IsFull())
        Wait[QueueLength++] = c;
}
int Queue::Extract()
{
    //���� � ������� ���� ��������, �� ���������� ���, //������� ����� ������ � �������� ������� 
    if (!IsEmpty()) {
        //��������� ������
        int temp = Wait[0];
        //�������� ��� ��������
        for (int i = 1; i < QueueLength; i++)
            Wait[i - 1] = Wait[i];

        //��������� ����������
        QueueLength--;
        //������� ������(�������)
        return temp;
    }
    else //���� � ����� ��������� ���
        return -1;
}
int Queue::Max_Element_Value() const
{
    int max = GetValue(0);

    for (size_t i = 0; i < GetCount(); i++)
        if (GetValue(i) > max)
            max = GetValue(i);
    
    return max;
}


class Taxi_Stop
{
    string stop_type;
    int Average_Passenger_Arrival[number_of_day_intervals];
    int Average_Taxi_Arrival[number_of_day_intervals]; 
    int QueueLength;
    const Day_Interval Day_Int[number_of_day_intervals]
    {
        {"Morning", 360}, {"Afternoon", 360}, {"Evening", 360}
    };
    int Taxi_Seats_Number;
public:
    Queue Pas_Arrivals;
    Queue Taxi_Arrivals;
    Queue Waiting_Pas;
    Queue Delivered_Pas;
    Queue Pas_On_Stop;
    Taxi_Stop();
    Taxi_Stop(int Pas_Arr[number_of_day_intervals], 
        int Taxi_Arr[number_of_day_intervals], int Queue);
    //passenger arrival
    void Arrival();
    //passengers departure
    void Departure(int c);
    //������� �������
    void Clear();
    //�������� ������������� ��������� � �������
    bool IsEmpty();
    //Quantity of passengers in queue
    int GetAverPasArr(int di) const;
    int GetAverTaxiArr(int ta) const;
    int GetQueueLength() const;
    int GetSeatsNum() const;
    string GetStopType() const;
    void SetQueueLength(int c);
    void SetAverPasArr();
    void SetAverTaxiArr();
    void SetStopType();
    void show() const;
    //int PasArrGen();
    //int TaxiArrGen();
    void Pas_and_TaxiArrGen();
    /*void Day_Delivery();*/
    int Aver_Pass_Time() const;
};

Taxi_Stop::Taxi_Stop(int Pas_Arr[number_of_day_intervals], 
    int Taxi_Arr[number_of_day_intervals], int Queue) :
    Average_Passenger_Arrival{ },
    Average_Taxi_Arrival{ },
    QueueLength{ Queue },
    stop_type {"usual"} 
{
    for (size_t i = 0; i < number_of_day_intervals; i++)
    {
        Average_Passenger_Arrival[i] = Pas_Arr[i];
        Average_Taxi_Arrival[i] = Taxi_Arr[i];
    }
    srand(time(NULL));
    Taxi_Seats_Number = rand() % 20 + 10;
}

Taxi_Stop::Taxi_Stop() : Taxi_Stop(nullptr, nullptr, 0){}


void Taxi_Stop::Clear()
{
    //����������� "�������" �������
    QueueLength = 0;
}
bool Taxi_Stop::IsEmpty()
{
    //����?
    return QueueLength == 0;
}
int Taxi_Stop::GetQueueLength() const
{
    return QueueLength;
}
int Taxi_Stop::GetAverPasArr(int di) const
{
    return Average_Passenger_Arrival[di];
}
int Taxi_Stop::GetAverTaxiArr(int ta) const
{
    return Average_Taxi_Arrival[ta];
}
string Taxi_Stop::GetStopType() const
{
    return stop_type;
}
int Taxi_Stop::GetSeatsNum() const
{
    return Taxi_Seats_Number;
}
void Taxi_Stop::Arrival()
{
    QueueLength++;
}
void Taxi_Stop::Departure(int c)
{
    QueueLength >= c ? QueueLength -= c : QueueLength = 0;
}
void Taxi_Stop::SetQueueLength(int c)
{
    QueueLength = c;
}
void Taxi_Stop::SetAverPasArr()
{
    for (size_t i = 0; i < number_of_day_intervals; i++)
    {
        cout << "Please enter average speed of passengers arrival in the " <<
            Day_Int[i].GetName() << " : ";
        cin >> Average_Passenger_Arrival[i];       
    }
    cout << endl;
}
void Taxi_Stop::SetAverTaxiArr()
{
    for (size_t i = 0; i < number_of_day_intervals; i++)
    {
        cout << "Please enter average speed of taxi arrival in the " <<
            Day_Int[i].GetName() << " : ";
        cin >> Average_Taxi_Arrival[i];
    }
    cout << endl;
}
void Taxi_Stop::SetStopType()
{
    int temp = 0;

    while (!(temp == 1 || temp == 2))
    {
        cout << "Please choose bus stop type. Choose \n";
        cout << " 1 - for usual stop;\n";
        cout << " 2 - for final stop.\n";
        cout << "Your choice: ";
        cin >> temp;
        cout << endl;

        if (!(temp == 1 || temp == 2))
            cout << "Error! Please make correct choice!\n";
    };

    temp == 1 ? stop_type = "usual" : stop_type = "final";
}
void Taxi_Stop::show() const
{
    for (size_t i = 0; i < number_of_day_intervals; i++)
    {
        cout << "Average speed of passengers arrival in the " <<
            Day_Int[i].GetName() << " : " << Average_Passenger_Arrival[i] << endl;
    }
    cout << endl;

    for (size_t i = 0; i < number_of_day_intervals; i++)
    {
        cout << "Average speed of taxi arrival in the " <<
            Day_Int[i].GetName() << " : " << Average_Taxi_Arrival[i] << endl;
    }
    cout << endl;

    cout << "Bus stop type is " << stop_type << endl;
}
//int Taxi_Stop::PasArrGen()
//{
//    int temp = 0;
//    int dur = 0;
//
//    for (size_t i = 0; i < number_of_day_intervals; i++)
//    {
//        int j = 1;
//        while (Average_Passenger_Arrival[i] * j <= Day_Int[i].GetDuration())
//        {
//            Pas_Arrivals.Add(Average_Passenger_Arrival[i] * j + dur);
//            temp++;
//            j++;
//        }
//        dur += Day_Int[i].GetDuration();
//    }
//
//    return temp;
//}
//int Taxi_Stop::TaxiArrGen()
//{
//    int temp = 0;
//    int dur = 0;
//
//    for (size_t i = 0; i < number_of_day_intervals; i++)
//    {
//        int j = 1;
//        while (Average_Taxi_Arrival[i] * j <= Day_Int[i].GetDuration())
//        {
//            Taxi_Arrivals.Add(Average_Taxi_Arrival[i] * j + dur);
//            temp++;
//            j++;
//        }
//
//        dur += Day_Int[i].GetDuration();
//        
//    }
//
//    return temp;
//}

void Taxi_Stop::Pas_and_TaxiArrGen()
{
    int temp1=0, temp2 = 0;
    int dur = 0;

    for (size_t i = 0; i < number_of_day_intervals; i++)
    {
        int j = 1; int k = 1;

        while (Average_Passenger_Arrival[i] * j <= Day_Int[i].GetDuration()
            || Average_Taxi_Arrival[i] * k <= Day_Int[i].GetDuration())
        {
            if (Average_Passenger_Arrival[i] * j <= Average_Taxi_Arrival[i] * k)
            {
                Pas_Arrivals.Add(Average_Passenger_Arrival[i] * j + dur);
                Waiting_Pas.Add(Average_Passenger_Arrival[i] * j + dur);
                Pas_On_Stop.Add(Waiting_Pas.GetCount());
                temp1++;
                j++;
            }
            else
            {
                Taxi_Arrivals.Add(Average_Taxi_Arrival[i] * k + dur);

                int j = 0;
                int l = 0;

                while (j < Taxi_Seats_Number && Waiting_Pas.GetValue(0) <=
                    Taxi_Arrivals.GetValue(Taxi_Arrivals.GetCount() - 1))
                {
                    if (!Waiting_Pas.IsEmpty())
                    {
                        int temp = Waiting_Pas.Extract();
                        l++;
                        Delivered_Pas.Add(-temp + Taxi_Arrivals.GetValue(i));
                    }
                    j++;
                }
                Pas_On_Stop.Add(Pas_On_Stop.GetValue(Pas_On_Stop.GetCount() - 1) - l);
                temp2++;
                k++;
            }
        }

        dur += Day_Int[i].GetDuration();

    }

}
//void Taxi_Stop::Day_Delivery()
//{
//    for (size_t i = 0; i < Pas_Arrivals.GetCount(); i++)
//        Waiting_Pas.Add(Pas_Arrivals.GetValue(i));
//
//    for (size_t i = 0; i < Taxi_Arrivals.GetCount(); i++)
//    {
//        int j = 0;
//
//        while (j < Taxi_Seats_Number && Waiting_Pas.GetValue(0) <= 
//            Taxi_Arrivals.GetValue(i))
//        {
//            if (!Waiting_Pas.IsEmpty())
//            {
//                int temp = Waiting_Pas.Extract();
//                Delivered_Pas.Add(-temp+Taxi_Arrivals.GetValue(i));
//            }
//            j++;
//        }
//
//    }
//}
int Taxi_Stop::Aver_Pass_Time() const
{
    int sum = 0;
    int temp;

    for (size_t i = 0; i < Delivered_Pas.GetCount(); i++)
        sum += Delivered_Pas.GetValue(i);

    if (Delivered_Pas.GetCount() != 0)
        temp = sum / Delivered_Pas.GetCount();

    return temp;
}


void main()
 {

    int pas[3]{ 30, 60, 45 };
    int tax[3]{ 360, 360, 360 };

    Taxi_Stop TS { pas, tax, 0 };

    //TS.SetAverPasArr();
    //TS.SetAverTaxiArr();
    //TS.SetStopType();
    TS.show();

    cout << "\nThere are " << TS.GetSeatsNum() << " seats in every Taxi\n";
    TS.Pas_and_TaxiArrGen();

    cout << "There wiil be " << TS.Pas_Arrivals.GetCount() << " passengers per day.\n";
    cout << "There wiil be " << TS.Taxi_Arrivals.GetCount() << " taxi per day.\n";
    cout << "These taxis could deliver " << TS.Taxi_Arrivals.GetCount() * TS.GetSeatsNum()
        << " passengers.\n";

   /* TS.Day_Delivery();*/

    cout << "Waiting passengers" << endl;
    TS.Waiting_Pas.Show();

    cout << "Delivered passengers" << endl;
    TS.Delivered_Pas.Show();

    cout << "Passengers on stop during a day" << endl;
    TS.Pas_On_Stop.Show();
    
    cout << "Average time of waiting of delivered passengers is " <<
        TS.Aver_Pass_Time() << endl;

    cout << "Maximum number of waiting passengers on stop was: " <<
        TS.Pas_On_Stop.Max_Element_Value() << endl;

    int max_people;

  /*  cout << "Please enter maximum of people on bus stop: ";
    cin >> max_people;*/

    max_people = 50;







}
