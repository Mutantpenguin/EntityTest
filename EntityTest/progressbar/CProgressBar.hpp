#pragma once

#include <chrono>

#include "../CSize.hpp"

class CProgressBar final
{
public:
	~CProgressBar();

	void Show( const u8 percent );
	void Finish();

private:
	static CSize TerminalSize();

	const CSize m_terminalSize = TerminalSize();

	u8 m_currentPercent = 0;

	std::chrono::time_point<std::chrono::system_clock> m_lastShowTime = std::chrono::system_clock::now();

	bool m_hasFinished = false;
};
