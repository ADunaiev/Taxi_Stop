#include <iostream>
#include <string.h>
#include <time.h>
#include <vector>
using namespace std;

//Задание 2.
//Создать имитационную модель «остановка маршрутных
//такси».
// 
//Необходимо вводить следующую информацию :
// - среднее время между появлениями пассажиров на остановке
// в разное время суток, 
// - среднее время между появлениями маршруток на остановке в разное время суток, 
// - тип остановки(конечная или нет).
// 
// Необходимо определить : 
// - среднее время пребывание человека на остановке, 
// - достаточный интервал времени между приходами маршруток, чтобы
//на остановке находилось не более N людей одновременно.
// 
// Количество свободных мест в маршрутке является случайной величиной.

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
    //Очередь
    int* Wait;
    //Максимальный размер очереди
    const int MaxQueueLength = 1000;
    //Текущий размер очереди
    int QueueLength;
public:
    //Конструктор
    Queue();
    //Деструктор
    ~Queue();
    //Добавление элемента
    void Add(int c);
    //Извлечение элемента
    int Extract();
    //Очистка очереди
    void Clear();
    //Проверка существования элементов в очереди
    bool IsEmpty();
    //Проверка на переполнение очереди
    bool IsFull();
    //Количество элементов в очереди
    int GetCount() const;
    int GetValue(int i) const;
    //демонстрация очереди
    void Show();
    int Max_Element_Value();
    int Get_Last_Value();
};

void Queue::Show()
{
    cout << "-----------------------------------\n";
    //демонстрация очереди
    for (int i = 0; i < QueueLength; i++)
    {
        cout << Wait[i] << " ";
    }
    cout << "\n-----------------------------------\n";
}
Queue::~Queue()
{
    //удаление очереди
    delete[]Wait;
}
Queue::Queue()
{
    //создаем очередь
    Wait = new int[MaxQueueLength];
    //Изначально очередь пуста
    QueueLength = 0;
}
void Queue::Clear()
{
    //Эффективная "очистка" очереди
    QueueLength = 0;
}
bool Queue::IsEmpty()
{
    //Пуст?
    return QueueLength == 0;
}
bool Queue::IsFull()
{
    //Полон?
    return QueueLength == MaxQueueLength;
}
int Queue::GetCount() const
{
    //Количество присутствующих в стеке элементов
    return QueueLength;
}
int Queue::GetValue(int i) const
{
    return Wait[i];
}
void Queue::Add(int c)
{
    //Если в очереди есть свободное место,
    //то увеличиваем количество
    //значений и вставляем новый элемент
    if (!IsFull())
        Wait[QueueLength++] = c;
}
int Queue::Extract()
{
    //Если в очереди есть элементы, то возвращаем тот, //который вошел первым и сдвигаем очередь 
    if (!IsEmpty()) {
        //запомнить первый
        int temp = Wait[0];
        //сдвинуть все элементы
        for (int i = 1; i < QueueLength; i++)
            Wait[i - 1] = Wait[i];

        //уменьшить количество
        QueueLength--;
        //вернуть первый(нулевой)
        return temp;
    }
    else //Если в стеке элементов нет
        return -1;
}
int Queue::Max_Element_Value()
{
    int max = GetValue(0);

    for (size_t i = 0; i < GetCount(); i++)
        if (GetValue(i) > max)
            max = GetValue(i);
    
    return max;
}
int Queue::Get_Last_Value()
{
    if (!IsEmpty())
    {
        return Wait[QueueLength - 1];
    }
      
    return 0;
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
    //Очистка очереди
    void Clear();
    //Проверка существования элементов в очереди
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
    void Pas_and_TaxiArrGen();
    int Aver_Pass_Time() const;
    void Print_Best_Intervals(int max);
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

Taxi_Stop::Taxi_Stop() :
    Average_Passenger_Arrival{ },
    Average_Taxi_Arrival{ },
    QueueLength{ 0 },
    stop_type{ "usual" }
{
    for (size_t i = 0; i < number_of_day_intervals; i++)
    {
        Average_Passenger_Arrival[i] = 0;
        Average_Taxi_Arrival[i] = 0;
    }
    srand(time(NULL));
    Taxi_Seats_Number = rand() % 20 + 10;
}


void Taxi_Stop::Clear()
{
    //Эффективная "очистка" очереди
    QueueLength = 0;
}
bool Taxi_Stop::IsEmpty()
{
    //Пуст?
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
void Taxi_Stop::Pas_and_TaxiArrGen()
{
    Pas_On_Stop.Clear();
    Pas_Arrivals.Clear();
    Taxi_Arrivals.Clear();
    Waiting_Pas.Clear();
    Delivered_Pas.Clear();

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

                int m = 0;
                int l = 0;
                
                while (m < Taxi_Seats_Number && (m+1) * Average_Passenger_Arrival[i] 
                    <= Average_Taxi_Arrival[i])
                {
                    if (!Waiting_Pas.IsEmpty())
                    {
                        int temp = Waiting_Pas.Extract();
                        l++;
                        Delivered_Pas.Add(-temp + Taxi_Arrivals.Get_Last_Value());
                    }
                    m++;
                }
                Pas_On_Stop.Add(Pas_On_Stop.Get_Last_Value() - l);
                temp2++;
                k++;
            }
        }

        dur += Day_Int[i].GetDuration();

    }

}
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
void Taxi_Stop::Print_Best_Intervals(int max)
{
    int temp;

    for (size_t i = 0; i < number_of_day_intervals; i++)
    {
        if (Taxi_Seats_Number <= max)
            temp = Taxi_Seats_Number * Average_Passenger_Arrival[i];
        else
            temp = max * Average_Passenger_Arrival[i];

        cout << "Best speed of taxi arrival in the " <<
            Day_Int[i].GetName() << " for " << max << " passengers: " 
            << temp << endl;
    } 
}

void main()
 {
    /*You can uncomment is for convenience*/
    //int pas[3]{ 10, 30, 20};
    //int tax[3]{ 100, 300, 200 };
    //Taxi_Stop TS { pas, tax, 0 };

    Taxi_Stop TS;

    TS.SetAverPasArr();
    TS.SetAverTaxiArr();
    TS.SetStopType();
    TS.show();

    cout << "\nThere are " << TS.GetSeatsNum() << " seats in every Taxi\n";
    TS.Pas_and_TaxiArrGen();

    cout << "There wiil be " << TS.Pas_Arrivals.GetCount() << " passengers per day.\n";
    cout << "There wiil be " << TS.Taxi_Arrivals.GetCount() << " taxi per day.\n";
    cout << "These taxis could deliver " << TS.Taxi_Arrivals.GetCount() * TS.GetSeatsNum()
        << " passengers.\n";

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

    cout << "\nPlease enter maximum of people on bus stop: ";
    cin >> max_people;
    
    TS.Print_Best_Intervals(max_people);
}
