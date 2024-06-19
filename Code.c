#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#define size 10
#define len 100
typedef struct stockinfo
{
  char name[100];
  float open;
  float high;
  float low;
  float closeprice;
  float volume;
}stock;
struct Date {
    int year;
    int month;
    int day;
};

int isLeapYear(int year) {
    if (year % 400 == 0)
        return 1;
    if (year % 100 == 0)
        return 0;
    if (year % 4 == 0)
        return 1;
    return 0;
}

int getDaysInMonth(int year, int month) {
    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year))
        return 29;
    return daysInMonth[month - 1];
}

int calculateNumOfDays(struct Date startDate, struct Date endDate) {
    int numOfDays = 0;
    int year,month;
    // Calculate the number of days for full years between the start and end dates
    for ( year = startDate.year; year < endDate.year; year++) {
        numOfDays += isLeapYear(year) ? 366 : 365;
    }

    // Calculate the number of days for the partial start year
    for ( month = startDate.month; month <= 12; month++) {
        int daysInMonth = getDaysInMonth(startDate.year, month);
        if (month == startDate.month)
            daysInMonth -= startDate.day - 1;
        numOfDays += daysInMonth;
    }

    // Calculate the number of days for the partial end year
    for ( month = 1; month < endDate.month; month++) {
        int daysInMonth = getDaysInMonth(endDate.year, month);
        numOfDays += daysInMonth;
    }
    numOfDays += endDate.day;

    return numOfDays-365;
}
//1) Function to calculate percentage change in price
float calculatePercentageChange(float start, float end) {
    return ((end - start) / start) * 100;
}

// Function to sort stocks based on volume and close prices
void sortStocks( stock stocks[], int numStocks, int day) {
    // Bubble sort
    int i,j;
    for ( i = 0; i < numStocks - 1; i++) {
        for ( j = 0; j < numStocks - i - 1; j++) {
            // Sort based on volume
            if (stocks[j].volume < stocks[j + 1].volume) {
                // Swap stocks
                 stock temp = stocks[j];
                stocks[j] = stocks[j + 1];
                stocks[j + 1] = temp;
            }
            // If volume is equal, sort based on close prices
            else if (stocks[j].volume == stocks[j + 1].volume) {
                if (stocks[j].closeprice > stocks[j + 1].closeprice) {
                    // Swap stocks
                     stock temp = stocks[j];
                    stocks[j] = stocks[j + 1];
                    stocks[j + 1] = temp;
                }
            }
        }
    }

    // Print sorted stocks
    printf("Sorted Stocks (Volume-wise, Close Price-wise) on Day %d:\n", day);
    for ( i = 0; i < numStocks; i++) {
        printf("%s\n", stocks[i].name);
    }
}

// Function to find profit/loss of stocks between two dates
/*void findProfitLoss( stock stocks[], int numStocks, struct Date start_date[], struct Date end_date[]) {
    float total_profit_loss = 0.0;
    int i,j;
    for ( i = 0; i < numStocks; i++) {
        // Find stock data for start and end dates
         stock start_stock, end_stock;
        int found_start = 0, found_end = 0;

        for ( j = 0; j < numStocks; j++) {
            if (strcmp(stocks[j].name, stocks[i].name) == 0) {
                if (strcmp(start_date, stocks[j]. == 0) {
                    start_stock = stocks[j];
                    found_start = 1;
                }
                if (strcmp(end_date, stocks[j].date) == 0) {
                    end_stock = stocks[j];
                    found_end = 1;
                }
            }
        }

        // Calculate profit/loss
        if (found_start && found_end) {
            float profit_loss = (end_stock.closeprice - start_stock.closeprice) / start_stock.closeprice * 100;
            total_profit_loss += profit_loss;
            printf("Profit/Loss for %s: %.2f%%\n", stocks[i].name, profit_loss);
        }
    }

    printf("Total Profit/Loss: %.2f%%\n", total_profit_loss);
}*/

// Function to find the highest performing stock
void findHighestPerformingStock( stock stocks[], int numStocks, char start_date[], char end_date[]) {
    char highest_stock[20];
    float highest_gain = 0.0;
    int i,j;
    for ( i = 0; i < numStocks; i++) {
        // Find stock data for start and end dates
         stock start_stock, end_stock;
        int found_start = 0, found_end = 0;

        for ( j = 0; j < numStocks; j++) {
            if (strcmp(stocks[j].name, stocks[i].name) == 0) {
                if (strcmp(start_date, stocks[j].date) == 0) {
                    start_stock = stocks[j];
                    found_start = 1;
                }
                if (strcmp(end_date, stocks[j].date) == 0) {
                    end_stock = stocks[j];
                    found_end = 1;
                }
            }
        }

        // Calculate percentage gain
        if (found_start && found_end) {
            float gain = calculatePercentageChange(start_stock.closeprice, end_stock.closeprice);
            if (gain > highest_gain) {
                highest_gain = gain;
                strcpy(highest_stock, stocks[i].name);
            }
        }
    }

    printf("Highest Performing Stock: %s\n", highest_stock);
}

// Function to find the lowest performing stock
void findLowestPerformingStock( stock stocks[], int numStocks, char start_date[], char end_date[]) {
    char lowest_stock[20];
    float lowest_gain = 0.0;
   int i,j;
    for ( i = 0; i < numStocks; i++) {
        // Find stock data for start and end dates
         stock start_stock, end_stock;
        int found_start = 0, found_end = 0;

        for ( j = 0; j < numStocks; j++) {
            if (strcmp(stocks[j].name, stocks[i].name) == 0) {
                if (strcmp(start_date, stocks[j].date) == 0) {
                    start_stock = stocks[j];
                    found_start = 1;
                }
                if (strcmp(end_date, stocks[j].date) == 0) {
                    end_stock = stocks[j];
                    found_end = 1;
                }
            }
        }

        // Calculate percentage gain
        if (found_start && found_end) {
            float gain = calculatePercentageChange(start_stock.close, end_stock.close);
            if (gain < lowest_gain) {
                lowest_gain = gain;
                strcpy(lowest_stock, stocks[i].name);
            }
        }
    }

    printf("Lowest Performing Stock: %s\n", lowest_stock);
}

// Function to list stocks by overall performance
void listStocksByOverallPerformance(struct Stock stocks[], int numStocks, char start_date[], char end_date[]) {
    // Calculate overall performance for each stock
    float overall_performance[MAX_STOCKS] = {0};
   int i,j;
    for ( i = 0; i < numStocks; i++) {
        // Find stock data for start and end dates
        struct Stock start_stock, end_stock;
        int found_start = 0, found_end = 0;

        for ( j = 0; j < numStocks; j++) {
            if (strcmp(stocks[j].name, stocks[i].name) == 0) {
                if (strcmp(start_date, stocks[j].date) == 0) {
                    start_stock = stocks[j];
                    found_start = 1;
                }
                if (strcmp(end_date, stocks[j].date) == 0) {
                    end_stock = stocks[j];
                    found_end = 1;
                }
            }
        }

        // Calculate percentage change compared to previous day multiplied by volume
        if (found_start && found_end) {
            float percentage_change = calculatePercentageChange(start_stock.close, end_stock.close);
            overall_performance[i] = percentage_change * end_stock.volume;
        }
    }

    // Sort stocks by overall performance
    for ( i = 0; i < numStocks - 1; i++) {
        for ( j = 0; j < numStocks - i - 1; j++) {
            if (overall_performance[j] > overall_performance[j + 1]) {
                // Swap stocks
                struct Stock temp = stocks[j];
                stocks[j] = stocks[j + 1];
                stocks[j + 1] = temp;

                // Swap overall performance values
                float temp_performance = overall_performance[j];
                overall_performance[j] = overall_performance[j + 1];
                overall_performance[j + 1] = temp_performance;
            }
        }
    }

    // Print stocks by overall performance
    printf("Stocks by Increasing Overall Performance:\n");
    for (int i = 0; i < numStocks; i++) {
        printf("%s\n", stocks[i].name);
    }
}

// Function to calculate the average value of all stocks
float calculateAverageValue(struct Stock stocks[], int numStocks) {
    float total_value = 0.0;
    int total_volume = 0;
int i;
    for ( i = 0; i < numStocks; i++) {
        total_value += stocks[i].close * stocks[i].volume;
        total_volume += stocks[i].volume;
    }

    return total_value / total_volume;
}
int main()
{
    stock stocks[size];char name[len];float open,low,high,closeprice,volume;
    struct Date start_date={2023,05,01};
    struct Date end_date={2023,05,10};printf("printing numofdays\n");
    int numdays = calculateNumOfDays(start_date, end_date);
    printf("%d\n",numdays);
    FILE* fp=fopen("stocks.txt","r");int j=0;
    while(!feof(fp))
    {
      j++;
        fscanf(fp,"%s",stocks[j].name);
        printf("%s\n",name);int i;
        for( i=1;i<=numdays;i++)
         {  fscanf(fp,"%f %f %f %f %f",&stocks[i].open,&stocks[i].low,&stocks[i].high,&stocks[i].closeprice,&stocks[i].volume);
            printf("%f %f %f %f %f\n",stocks[i].open,stocks[i].low,stocks[i].high,stocks[i].closeprice,stocks[i].volume);
         }
    } struct Date sd,ed;
    printf("Enter Start date\n");
    scanf("%d %d %d",sd.year,sd.month,sd.day);scanf("%d %d %d",ed.year,ed.month,ed.day);
    int sp=sd.day-start_date.day;int ep=end_date.day-ed.day;
    



}
