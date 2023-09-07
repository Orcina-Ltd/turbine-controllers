#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include "OrcFxAPI.h"

using namespace Orcina;

enum class ControlledVar { pitch, torque };

void print(const std::wstring text);
bool checkStatus(TExtFnInfo& info, const std::wstring context, int status);
std::string utf16ToUtf8(const std::wstring& value);
std::wstring utf8ToUtf16(const std::string value);
std::wstring trim(const std::wstring& str);
double radians(const double degrees);
TVector crossProd(const TVector& v1, const TVector& v2);
TVector sum(const TVector& v1, const TVector& v2);
TVector prod(const TMatrix& m, const TVector& v);
bool isZero(const TVector& v);
double suppressRangeJumps(const double previous, const double value);
ControlledVar controlledVar(const std::wstring dataName);
bool TryStrToDouble(const std::string& text, double& value);