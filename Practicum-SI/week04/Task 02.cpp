#include <iostream>

class Task
{
private:
    char condition[256];
    char password[9];
    int failedLogins;
    int points;

    void setConditionInternal(const char* newCond)
    {
        if (strlen(newCond) == 256)
        {
            strcpy(condition, newCond);
        }
        else return;
    }

    void setPasswordInternal(const char* newPass)
    {
        if (strlen(newPass) == 9)
        {
            strcpy(condition, newPass);
        }
        else return;
    }

    void setFailedLoginInternal()
    {
        failedLogins = 0;
    }

    void setPointsInternal(int a)
    {
        points = a;
    }


public:

    void setPoints(int a) 
    {
        points = a;
    }

    void setPassword(const char* newPass, const char* oldPass)
    {
        if (strcmp(oldPass, password) == 0)
        {
            if (strlen(newPass) == 9)
            {
                strcpy(password, newPass);
            }
            else return;
        }
        
        else return;
    }

    void setTask(const char* task, const char* passwd)
    {
        if (strcmp(passwd, password) == 0)
        {
            if (strlen(task) == strlen(condition))
            {
                strcpy(condition, task);
            }
            else return;
        }
        else return;
    }

    int getPoints() const
    {
        return points;
    }

    const char* getTask(const char* passwd) 
    {
        if (strcmp(password, passwd) == 0)
        {
           return condition;
        }
        else
        {
            setPoints(getPoints()+1);
            return nullptr;
        }
    }

    int getLoginFails()
    {
        return failedLogins;
    }

    //не мисл€, че тр€бва да имаме setLoginFails, защото в началото мога да си го set-na на 0 и впоследствие н€ма да имам нужда да промен€м бро€.

    Task(const char* condition2, const char* passwd, int pts)
    {
        setConditionInternal(condition);
        setPasswordInternal(passwd);
        setFailedLoginInternal();
        setPointsInternal(pts);
    }
};


int main()
{
    std::cout << "Hello World!\n";
}