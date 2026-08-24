#include "precomp.h"
#include <regex>
#include "SeparatorTrace.h"
#include "FilterCommon.h"
#include "BarcodeDataAttributes.h"
#include "BarcodeDataAttributes.tmh"

BarcodeDataAttributes::BarcodeDataAttributes(
    __in const CStringW pathDataString,
    __in const float strokeThickness)
    : _strokeThickness(strokeThickness)
{
    ParseForBarcode(pathDataString);
}

bool BarcodeDataAttributes::IsValidBarcode() const
{
    return _isValidBarcode;
}

CStringW BarcodeDataAttributes::GetAdjustedDataPathString()
{
    AdjustCoordinates();

    CStringW dataPathString;
    dataPathString.Format(L"M %.2f,%.2f L %.2f,%.2f %.2f,%.2f %.2f,%.2f z",
        _horizontalStartPosition,
        _verticalStartPosition,
        _horizontalStartPositionPlusSize,
        _verticalStartPosition,
        _horizontalStartPositionPlusSize,
        _verticalStartPositionPlusSize,
        _horizontalStartPosition,
        _verticalStartPositionPlusSize);

    return dataPathString;
}

float BarcodeDataAttributes::GetHorizontalStartPosition() const
{
    return _horizontalStartPosition;
}

float BarcodeDataAttributes::GetHorizontalStartPositionPlusSize() const
{
    return _horizontalStartPositionPlusSize;
}

float BarcodeDataAttributes::GetVerticalStartPosition() const
{
    return _verticalStartPosition;
}

float BarcodeDataAttributes::GetVerticalStartPositionPlusSize() const
{
    return _verticalStartPositionPlusSize;
}

////////////////////////////////////////////////////////////////////////////////
// BarcodeDataAttributes::ParseForBarcode()
//
// we expect an incoming string like one of these:
//
//    M19.2,179.52L18.88,179.52 18.88,199.68 19.2,199.68Z
//
//    F0 M 19.2,179.52 L 18.88,179.52 18.88,199.68 19.2,199.68 z
//
// we parse it for pairs of coordinates; populate all the floats in our class.
//
// use this Regular Expression (regex):   [-+]?[0-9]*\.?[0-9]+ for a float
// from this page: http://www.regular-expressions.info/floatingpoint.html
//
////////////////////////////////////////////////////////////////////////////////
void BarcodeDataAttributes::ParseForBarcode(
    __in const CStringW incomingPathDataString)
{
    _isValidBarcode = false;
    _horizontalStartPosition = 0.0f;
    _verticalStartPosition = 0.0f;
    _horizontalStartPositionPlusSize = 0.0f;
    _verticalStartPositionPlusSize = 0.0f;

    const std::wstring floatRegexString(LR"([-+]?[0-9]*\.?[0-9]+)");
    const std::wstring twoFloatsCommaSeparatedString(floatRegexString + L"[ ]*,[ ]*" + floatRegexString);
    const std::wregex dataPairsRegex(twoFloatsCommaSeparatedString);

    std::wstring pathDataString = RemoveLeadingF0(incomingPathDataString);

    std::wsmatch match;
    bool matched = std::regex_search(pathDataString, match, dataPairsRegex);
    if (!matched) {
        DoTraceMessage(WS_ERROR, "parse failed on data match 1 of 4: %ls", incomingPathDataString);
        return;
    }

    POINTF point1 {};
    POINTF point2 {};
    POINTF point3 {};
    POINTF point4 {};

    std::wstring commaSeparatedFloatStrings = match[0];
    auto twoFloatStrings = FilterCommon::Split_String(commaSeparatedFloatStrings, L",");
    point1.x = std::stof(twoFloatStrings[0]);
    point1.y = std::stof(twoFloatStrings[1]);

    // move to the 2nd pair of floats:
    pathDataString = match.suffix();
    match = {};
    matched = std::regex_search(pathDataString, match, dataPairsRegex);
    if (!matched) {
        DoTraceMessage(WS_ERROR, "parse failed on data match 2 of 4: %ls", incomingPathDataString);
        return;
    }
    commaSeparatedFloatStrings = match[0];
    twoFloatStrings = FilterCommon::Split_String(commaSeparatedFloatStrings, L",");
    point2.x = std::stof(twoFloatStrings[0]);
    point2.y = std::stof(twoFloatStrings[1]);

    // move to the 3rd pair of floats:
    pathDataString = match.suffix();
    match = {};
    matched = std::regex_search(pathDataString, match, dataPairsRegex);
    if (!matched) {
        DoTraceMessage(WS_ERROR, "parse failed on data match 3 of 4: %ls", incomingPathDataString);
        return;
    }
    commaSeparatedFloatStrings = match[0];
    twoFloatStrings = FilterCommon::Split_String(commaSeparatedFloatStrings, L",");
    point3.x = std::stof(twoFloatStrings[0]);
    point3.y = std::stof(twoFloatStrings[1]);

    // move to the 4th pair of floats:
    pathDataString = match.suffix();
    match = {};
    matched = std::regex_search(pathDataString, match, dataPairsRegex);
    if (!matched) {
        DoTraceMessage(WS_ERROR, "parse failed on data match 4 of 4: %ls", incomingPathDataString);
        // ok to proceed...4th pair is optional.
    }
    else {
        commaSeparatedFloatStrings = match[0];
        twoFloatStrings = FilterCommon::Split_String(commaSeparatedFloatStrings, L",");
        point4.x = std::stof(twoFloatStrings[0]);
        point4.y = std::stof(twoFloatStrings[1]);
    }

    _isValidBarcode = IsValidShapeForBarcode(point1, point2, point3, point4);
    if (_isValidBarcode) {
        // NOTE: don't need the fourth point to get coords...
        SetPathDataCoordinates(point1, point2, point3);
    }
}

bool BarcodeDataAttributes::IsValidShapeForBarcode(
    __in const POINTF p1,
    __in const POINTF p2,
    __in const POINTF p3,
    __in const POINTF p4)
{
    if (p1.y != p2.y)   return false;
    if (p2.x != p3.x)   return false;
    if (p4.x != p1.x)   return false;
    if (p4.y != p3.y)   return false;

    //  line is OK make sure we don't have
    //  a point...
    if ((p2.y == p3.y) && (p1.x == p2.x)) {
        return false;
    }

    // PRINTDRV-421: check ratio of height and width...
    float height = abs(p1.y - p3.y);
    float width = abs(p1.x - p2.x);
    float ratio = (height > width) ? height / width : width / height;

    const bool isValidShapeForBarcode = (ratio > 10.0f);
    return isValidShapeForBarcode;
}

void BarcodeDataAttributes::SetPathDataCoordinates(
    __in const POINTF p1,
    __in const POINTF p2,
    __in const POINTF p3)
{
    _horizontalStartPosition = p1.x;
    _verticalStartPosition = p1.y;
    _horizontalStartPositionPlusSize = p2.x;
    _verticalStartPositionPlusSize = p3.y;
}

////////////////////////////////////////////////////////////////////////////////
// BarcodeDataAttributes::RemoveLeadingF0()
//
// XPS markup for a Path element's Data attribute might have a leading 'F0'
// string. Nuke it.
////////////////////////////////////////////////////////////////////////////////
CStringW BarcodeDataAttributes::RemoveLeadingF0(CStringW dataString)
{
    const CStringW f0String = L"F0";
    CStringW result = dataString;
    int position = dataString.Find(f0String);
    if (-1 != position) {
        result = dataString.Mid(position + f0String.GetLength());
    }
    return result;
}

void BarcodeDataAttributes::AdjustCoordinates()
{
    float horizontalWidth = _horizontalStartPositionPlusSize - _horizontalStartPosition;
    float verticalWidth = _verticalStartPositionPlusSize - _verticalStartPosition;
    float narrowWidth {};
    NarrowOrientation narrowOrientation {};

    if (abs(horizontalWidth) > abs(verticalWidth)) {
        narrowWidth = verticalWidth;
        narrowOrientation = verticalOrientation;
    }
    else {
        narrowWidth = horizontalWidth;
        narrowOrientation = horizontalOrientation;
    }

    float drawDirection = (narrowWidth >= 0.0f) ? 1.0f : -1.0f;
    float widthAdjustment = (_strokeThickness * 0.5f) * drawDirection;
    if (narrowOrientation == horizontalOrientation) {
        _horizontalStartPosition -= widthAdjustment;
        _horizontalStartPositionPlusSize += widthAdjustment;
    }
    else {
        _verticalStartPosition -= widthAdjustment;
        _verticalStartPositionPlusSize += widthAdjustment;
    }
}