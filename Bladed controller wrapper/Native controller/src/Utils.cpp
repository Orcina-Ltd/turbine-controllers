#include "Utils.hpp"
#include <charconv>

void print(const std::wstring text)
{
    int status(0);
    C_ExternalFunctionPrint(text.c_str(), &status); // ignore status
}

bool checkStatus(TExtFnInfo& info, const std::wstring context, int status)
{
    if (status == stOK)
        return true;

    int length = C_GetLastErrorStringW(nullptr);
    std::vector<wchar_t> error(length);
    C_GetLastErrorStringW(&error[0]);

    std::wstringstream msg;
    msg << context << L" failed with status code " << status << ": " << std::wstring(&error[0], length-1);
    C_RecordExternalFunctionError(&info, msg.str().c_str(), &status); // ignore status
    return false;
}

std::string utf16ToUtf8(const std::wstring& value)
{
    std::string result;
    int retval = WideCharToMultiByte(CP_UTF8, 0, value.c_str(), value.size(), nullptr, 0, nullptr, nullptr);
    result.resize(retval);
    retval = WideCharToMultiByte(CP_UTF8, 0, value.c_str(), value.size(), result.data(), retval, nullptr, nullptr);
    if (value.size() > 0 && retval == 0)
        throw std::runtime_error("Conversion failure: utf16 to utf8.");
    return result;
}

std::wstring utf8ToUtf16(const std::string value)
{
    std::wstring result;
    int retval = MultiByteToWideChar(CP_UTF8, 0, value.c_str(), value.size(), nullptr, 0);
    result.resize(retval);
    retval = MultiByteToWideChar(CP_UTF8, 0, value.c_str(), value.size(), result.data(), retval);
    if (value.size() > 0 && retval == 0)
        throw std::runtime_error("Conversion failure: utf8 to utf16.");
    return result;
}

std::wstring trim(const std::wstring& str)
{
    std::wstring result = str;
    result.erase(result.find_last_not_of(' ') + 1);
    result.erase(0, result.find_first_not_of(' '));
    return result;
}

double radians(const double degrees)
{
    return degrees * (M_PI / 180);
}

TVector crossProd(const TVector& v1, const TVector& v2)
{
    TVector result;
    result.X = v1.Y * v2.Z - v1.Z * v2.Y;
    result.Y = v1.Z * v2.X - v1.X * v2.Z;
    result.Z = v1.X * v2.Y - v1.Y * v2.X;
    return result;
}

TVector sum(const TVector& v1, const TVector& v2)
{
    TVector result;
    result.X = v1.X + v2.X;
    result.Y = v1.Y + v2.Y;
    result.Z = v1.Z + v2.Z;
    return result;
}

TVector prod(const TMatrix& m, const TVector& v)
{
    TVector result;
    result.X = m.X.X * v.X + m.X.Y * v.Y + m.X.Z * v.Z;
    result.Y = m.Y.X * v.X + m.Y.Y * v.Y + m.Y.Z * v.Z;
    result.Z = m.Z.X * v.X + m.Z.Y * v.Y + m.Z.Z * v.Z;
    return result;
}

bool isZero(const TVector& v)
{
    return v.X == 0 && v.Y == 0 && v.Z == 0;
}

double suppressRangeJumps(const double previous, const double value)
{
    if (std::isnan(previous))
        return value;

    // make sure that previous differs from value by no more than 360/2 by shifting value by an integer multiple of 360
    double difference = value - previous;
    if (std::abs(difference) > 180)
        return previous - 180 + std::fmod(difference + 180, 360);
    return value;
}

ControlledVar controlledVar(const std::wstring dataName)
{
    if (dataName == L"PitchController")
        return ControlledVar::pitch;
    if (dataName == L"GeneratorTorqueController")
        return ControlledVar::torque;
    throw std::runtime_error("Turbine controller can only be used to control pitch or torque.");
}

bool TryStrToDouble(const std::string& text, double& value)
{
    auto first = text.find_first_not_of(' ');
    auto last = 1 + text.find_last_not_of(' ');
    auto ptr = text.c_str();
    auto retval = std::from_chars(ptr + first, ptr + last, value);
    return retval.ec == std::errc() && retval.ptr == ptr + last;
}