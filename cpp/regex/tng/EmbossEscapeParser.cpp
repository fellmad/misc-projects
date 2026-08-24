////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Datacard Corporation.  All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////
#include "precomp.h"
#include <atlstr.h>
#include <string>
#include <regex>
#include "PagePrepTrace.h"
#include "EmbossEscapeParser.h"
#include "EmbossEscapeParser.tmh"

/*
valid incoming escape strings look like this. the escape prefix
followed by a font number; x cooridinate; y cooridinate; and
the  emboss data string.

~Em%1; 2; 3;    data with 4 leading blanks and ending semicolon;
~EM%1;307;328; BILL MEILACH
~EM%1;307;480;         10/2016
~EM%2;400;848;1111 2222 3333 4444
~EM%4;1221;1000;1111 2222 3333 4444
~EM%4;2000;1000;KEN C. FISCHER at 2000, 1000 mils font 4
*/

////////////////////////////////////////////////////////////////////////////////
// EmbossEscapeParser::Parse()
//
// search the incoming string for an Emboss escape. If found, populate an
// EmbossInfo data structure and return TRUE.
//
// If not found, return FALSE.
////////////////////////////////////////////////////////////////////////////////
bool EmbossEscapeParser::Parse(
    __in PWCHAR textToParse,
    __in const UINT textLength,
    __inout EmbossInfo& embossInfo)
{
    CStringW escapeString(textToParse, textLength);
    std::wstring escape_wstring = std::wstring(escapeString);

    const std::wregex embossRegex(LR"(~EM%(\d);\s*(\d+);\s*(\d+);(.*))", std::regex::icase);

    std::wsmatch match;
    const bool matched = std::regex_match(escape_wstring, match, embossRegex);
    if (!matched) {
        return false;
    }

    // we matched our regex to the incoming emboss escape string.
    // we have 5 match groups. match[0] is the entire string; ignore it.
    const short fontNumber = short(std::stoi(match[1]));
    const short horzMils = short(std::stoi(match[2]));
    const short vertMils = short(std::stoi(match[3]));
    const CComBSTR stringData = match[4].str().c_str();

    const EmbossInfo collectedInfo(
        fontNumber,
        horzMils,
        vertMils,
        stringData);

    embossInfo = collectedInfo;

    return true;
}