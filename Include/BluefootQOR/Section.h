//Section.h

//Defines an section element of a pipeline
#include "Element.h"

//------------------------------------------------------------------------------
namespace nsBluefoot
{
	//------------------------------------------------------------------------------
	class CAbstractSection : public CAbstractElement
	{
	public:

		CAbstractSection();
		virtual ~CAbstractSection();
		CAbstractSection(const CAbstractSection& src);
		CAbstractSection& operator = (const CAbstractSection& src);

	protected:

		CAbstractElement* m_pSource;
		CAbstractElement* m_pSink;
	};

	//------------------------------------------------------------------------------
	template< typename TSourceUnit, typename TSinkUnit >
	class CSection : public CAbstractElement
	{
	public:

		CSection();
		virtual ~CSection();
		CSection(const CSection& src);
		CSection& operator = (const CSection& src);

		//------------------------------------------------------------------------------
		virtual bool Read( byte* pDestBuffer, unsigned long ulNumberOfUnitsToRead, unsigned long& ulNumberOfUnitsRead)			//Read from this element into the buffer of the Sink
		{
		}

		//------------------------------------------------------------------------------
		virtual bool Write( byte* pSourceBuffer, unsigned long ulNumberOfUnitsToWrite, unsigned long& ulNumberOfUnitsWritten )	//Write to this element
		{
		}

	protected:

		CElement< TSourceUnit >* m_pSource;
		CElement< TSinkUnit >* m_pSink;
	};

}//nsBluefoot

