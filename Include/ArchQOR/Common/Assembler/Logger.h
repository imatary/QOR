//Logger.h

// Copyright (c) 2008-2010, Petr Kobalicek <kobalicek.petr@gmail.com>
// Copyright (c) Querysoft Limited 2012
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

#ifndef ARCHQOR_LOGGER_H_2
#define ARCHQOR_LOGGER_H_2

#include "CodeQOR/Macros/codingmacros.h"

//------------------------------------------------------------------------------
namespace nsArch
{
	struct LogFile;

	//------------------------------------------------------------------------------
	// Abstract logging class.
	//
	// This class can be inherited and reimplemented to fit into your logging
	// subsystem. When reimplementing use Logger::log() method to
	// log into your stream.
	//
	// This class also contain an m_bEnabled member that can be used to enable or disable logging.
	class __QOR_INTERFACE( __ARCHQOR ) CLogger
	{		
	public:

		CLogger() __QCMP_THROW;
		virtual ~CLogger() __QCMP_THROW;

		virtual void logString( const char* buf, Cmp_uint_ptr len = (Cmp_uint_ptr)-1 ) __QCMP_THROW = 0;		// Default implementation that is in CLogger is to do nothing.
		virtual void logFormat( const char* fmt, ... ) __QCMP_THROW;		// Log formatter message (like sprintf) sending output to logString() method.

		//------------------------------------------------------------------------------
		inline bool isEnabled() const __QCMP_THROW							// Return true if logging is enabled.
		{ 
			return m_bEnabled; 
		}

		virtual void setEnabled( bool enabled ) __QCMP_THROW;				// Set logging to enabled or disabled.

		//------------------------------------------------------------------------------
		// Get whether the logger should be used.
		inline bool isUsed() const __QCMP_THROW 
		{ 
			return m_bUsed; 
		}

		//------------------------------------------------------------------------------
		// Get whether logging binary output.
		inline bool getLogBinary() const 
		{ 
			return m_bLogBinary; 
		}

		//------------------------------------------------------------------------------
		//Set whether to log binary output.
		inline void setLogBinary( bool val ) 
		{ 
			m_bLogBinary = val; 
		}

	protected:
				
		bool m_bEnabled;			// Whether logger is enabled or disabled. Default true.

		// Whether logger is enabled and can be used.
		//
		// This value can be set by inherited classes to inform Logger that
		// assigned stream (or something that can log output) is invalid. If
		// m_bUsed is false it means that there is no logging output and ArchQOR
		// shouldn't use this logger (because all messages will be lost).
		//
		// This is designed only to optimize cases that logger exists, but its
		// configured not to output messages. The API inside Logging and ArchQOR
		// should only check this value when needed. The API outside ArchQOR should
		// check only whether logging is m_bEnabled.
		
		bool m_bUsed;			// Default true.
		bool m_bLogBinary;		// Whether to log instruction in binary form.

	private:

		bool bAlignmentDummy;

		__QCS_DECLARE_NONCOPYABLE( CLogger );
	};

	//------------------------------------------------------------------------------
	// Logger that can log to standard C FILE* stream.
	class __QOR_INTERFACE( __ARCHQOR ) CFileLogger : public CLogger
	{
	public:
				
		CFileLogger( LogFile* stream = 0 ) __QCMP_THROW;		// FILE stream where logging will be sent (can be NULL to disable logging).
		virtual void logString( const char* buf, Cmp_uint_ptr len = (Cmp_uint_ptr)-1 ) __QCMP_THROW;
		virtual void setEnabled( bool enabled ) __QCMP_THROW;

		//------------------------------------------------------------------------------
		// Get FILE* stream. Note Return value can be NULL.
		inline LogFile* getStream() const __QCMP_THROW 
		{ 
			return m_pStream; 
		}
		
		void setStream( LogFile* stream ) __QCMP_THROW;		//Set FILE* stream. stream FILE stream where to log output (can be NULL to disable logging).

	protected:
		
		LogFile* m_pStream;		// C file stream.

		__QCS_DECLARE_NONCOPYABLE( CFileLogger );
	};

}//nsArch

#endif //ARCHQOR_LOGGER_H_2
