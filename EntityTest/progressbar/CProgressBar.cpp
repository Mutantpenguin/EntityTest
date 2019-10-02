#include "CProgressBar.hpp"

#include <iostream>

#include "ext/fmt/format.h"
#include "ext/fmt/color.h"

#ifdef __linux__
	#include <sys/ioctl.h>
	#include <stdio.h>
	#include <unistd.h>
#elif _WIN32
	#include <windows.h>
#else
	#error "unsupported platform"
#endif

CProgressBar::~CProgressBar()
{
	if( !m_hasFinished )
	{
		Finish();
	}
}

void CProgressBar::Show( const u8 percent )
{
	const auto now = std::chrono::system_clock::now();

	// only show when at the start or the end
	// or when the percentage changed, but maximal every 200 milliseconds
	if( ( percent == 0 )
		||
		( percent == 100 )
		||
		( ( percent != m_currentPercent )
			&&
			( m_lastShowTime + std::chrono::milliseconds( 200 ) <= now ) ) )
	{
		m_currentPercent = percent;
		m_lastShowTime = now;

		const u8 progressWidth = ( m_terminalSize.width / 2 );

		std::string output;
		output.append( progressWidth / 100.0f * percent, '=' );
		
		if( percent < 100 )
		{
			output += '>';
		}

		fmt::print( "[{0:<{1}}] {2:>3}%\r", output, progressWidth, percent );
	}
}

void CProgressBar::Finish()
{
	m_hasFinished = true;

	fmt::print( "\n" );
}

CSize CProgressBar::TerminalSize()
{
#ifdef __linux__
	struct winsize w;
	ioctl( STDOUT_FILENO, TIOCGWINSZ, &w );

	return( CSize( w.ws_col, w.ws_row ) );
#elif _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
	
	const int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	const int rows    = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return( CSize( columns, rows ) );
#else
	#error "unsupported platform"
#endif
}