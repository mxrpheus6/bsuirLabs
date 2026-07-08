#include "battery.h"

int main(int argc, char* argv[])
{
    Battery battery = Battery();

    if (argc == 1) {
        while (true) {
            battery.writeBatteryInfoToFile("logs.log");
            battery.printBatteryInfo();
            Sleep(1000); 
            system("cls");
            battery.setBatteryInfo();
        }
    }

    std::string arg = argv[1];
    if (arg == "--hibernate") {
        if (!SetSuspendState(TRUE, FALSE, FALSE)) {
            std::cerr << "Перейти в режим гибернации не удалось..." << std::endl;
        }
        else {
            std::cout << "Переход в режим гибернации!" << std::endl;
        }
    }
    else if (arg == "--sleep") {
        if (!SetSuspendState(FALSE, FALSE, FALSE)) {
            std::cerr << "Перейти в режим сна не удалось..." << std::endl;
        }
        else {
            std::cout << "Переход в режим сна!" << std::endl;
        }
    }
    else {
        std::cerr << "Неизвестный флаг" << std::endl;
    }

    return 0;
}
