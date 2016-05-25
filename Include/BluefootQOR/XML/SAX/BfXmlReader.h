//BfXmlReader.h

// Copyright Querysoft Limited 2015
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

// XML Reader

#ifndef BLUEFOOT_XML_SAX_READER_H_3
#define BLUEFOOT_XML_SAX_READER_H_3

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/Text/TString.h"
#include "BluefootQOR/BfSource.h"
#include "BluefootQOR/XML/SAX/BfXmlEntityResolver.h"
#include "BluefootQOR/XML/SAX/BfXmlDTDHandler.h"
#include "BluefootQOR/XML/SAX/BfXmlContentHandler.h"
#include "BluefootQOR/XML/SAX/BfXmlErrorHandler.h"
#include "BluefootQOR/XML/SAX/BfXmlLexicalHandler.h"
#include "BluefootQOR/XML/SAX/BfXmlDeclHandler.h"

//------------------------------------------------------------------------------
namespace nsBluefoot
{
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __BLUEFOOTQOR ) CXmlReader
	{
	public:

		__QOR_DECLARE_OCLASS_ID( CXmlReader );

		virtual ~CXmlReader() {}
		
		virtual bool Feature( const nsCodeQOR::CUCS2String& name, bool *ok = 0 ) const = 0;
		virtual void SetFeature( const nsCodeQOR::CUCS2String& name, bool value ) = 0;
		virtual bool HasFeature( const nsCodeQOR::CUCS2String& name ) const = 0;

		virtual void* Property( const nsCodeQOR::CUCS2String& name, bool *ok = 0 ) const;
		virtual void SetProperty( const nsCodeQOR::CUCS2String& name, void* value );
		virtual bool HasProperty( const nsCodeQOR::CUCS2String& name ) const;

		virtual bool Parse( const CBFSource* input, bool incremental = false ) = 0;

		nsCodeQOR::CSTMember< CXmlEntityResolver > EntityResolver;
		nsCodeQOR::CSTMember< CXmlDTDHandler > DTDHandler;
		nsCodeQOR::CSTMember< CXmlContentHandler > ContentHandler;
		nsCodeQOR::CSTMember< CXmlErrorHandler > ErrorHandler;
		nsCodeQOR::CSTMember< CXmlLexicalHandler > LexicalHandler;
		nsCodeQOR::CSTMember< CXmlDeclHandler > DeclHandler;
	};

}//nsBluefoot

#endif//BLUEFOOT_XML_SAX_READER_H_3