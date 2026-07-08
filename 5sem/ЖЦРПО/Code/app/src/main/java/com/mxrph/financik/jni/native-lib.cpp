#include <jni.h>
#include <string>
#include <sstream>

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_mxrph_financik_HistoryActivity_isDateInMonth(JNIEnv *env, jobject /* this */, jstring date, jint selectedDay, jint selectedMonth, jint selectedYear) {
    const char *dateChars = env->GetStringUTFChars(date, 0);
    std::string dateStr(dateChars);
    env->ReleaseStringUTFChars(date, dateChars);

    std::istringstream dateStream(dateStr);
    std::string dayPart, monthPart, yearPart;

    if (std::getline(dateStream, dayPart, '/') &&
        std::getline(dateStream, monthPart, '/') &&
        std::getline(dateStream, yearPart)) {

        int day = std::stoi(dayPart);
        int month = std::stoi(monthPart) - 1;
        int year = std::stoi(yearPart);

        return year == selectedYear && month == selectedMonth;
    }

    return false;
}
