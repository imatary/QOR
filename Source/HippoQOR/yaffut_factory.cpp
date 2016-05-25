//yaffut_factory.cpp

#include "HippoQOR/yaffut.h"

//------------------------------------------------------------------------------
namespace yaffut
{
	//------------------------------------------------------------------------------
	Factory::Factory()
	{
	}

	//------------------------------------------------------------------------------
	Factory::~Factory()
	{
	}

	//------------------------------------------------------------------------------
	bool Factory::EqualsSuiteName (std::string const &name, std::string const& s)
	{
		return name.find (':') >= name.length () - 2 && s.substr (0, name.length ()) == name;
	}

	//------------------------------------------------------------------------------
	Factory& Factory::Instance()
	{
		static Factory instance;
		return instance;
	}

	//------------------------------------------------------------------------------
	void Factory::Register(const std::string& name, Create_t create)
	{
		m_Tests[name] = create;
	}

	//------------------------------------------------------------------------------
	size_t Factory::Fail() 
	{ 
		return m_fail; 
	}

	//------------------------------------------------------------------------------
	void Factory::List(const std::string& name)
	{
		size_t i = 0;
		for( Tests_t::const_iterator it = m_Tests.begin(); it != m_Tests.end(); ++it )
		{
			if(name.empty () || it->first == name || EqualsSuiteName (name, it->first) )
			{
				std::cerr << i++ << ")\t";
			}
			std::cout << it->first << std::endl;
		}
	}

	//------------------------------------------------------------------------------
	void Factory::Run(const std::string& name)
	{
		int i = -1;
		for(Tests_t::const_iterator it = m_Tests.begin(); it != m_Tests.end(); ++it)
		{
			++i;
			if("All" == name || it->first == name || EqualsSuiteName (name, it->first))
			{
				try
				{
					std::cout << std::endl << i << ") " << it->first << std::flush;
					{
						it->second();
					}
					std::cout << " [OK]" << std::flush;
					++m_pass;
				}
				catch(const std::exception& e)
				{
					std::cout << " [FAIL]\n  " << e.what() << std::flush;
					++m_fail;
				}
				catch(...)
				{
					std::cout << " [FAIL]\n  unknown exception" << std::flush;
					++m_fail;
				}
			}
		}
	}

	//------------------------------------------------------------------------------
	void Factory::Report()
	{
		const size_t size = m_Tests.size();
		std::cout << std::endl;
		std::cout << "[TOTAL](" << m_pass + m_fail << '/' << size << ")" << std::endl;
		std::cout << "[OK](" << m_pass << '/' << size << ")" << std::endl;
		if (m_fail)
		{
			std::cout << "[FAIL](" << m_fail << '/' << size << ")" << std::endl;
		}
	}

	//------------------------------------------------------------------------------
	int Factory::Main (int argc, const char* argv[])
	{
		if(argc > 1 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help"))
		{
			std::cout << "Yaffut - Yet Another Framework For Unit Testing.\n\n"
			"Usage: yaffut [OPTION] [Suite:|Suite::Test]...\n\n"
			"Options:\n"
			"  -h, --help     show this help\n"
			"  -l, --list     list test cases\n"
			"  -v, --version  show version number\n"
			<< std::flush;
			return 0;
		}

		if(argc > 1 && (std::string(argv[1]) == "-l" || std::string(argv[1]) == "--list"))
		{
			Factory::Instance().List(argc > 2 ? argv[2] : "");
			return 0;
		}

		if(argc > 1 && (std::string(argv[1]) == "-v" || std::string(argv[1]) == "--version"))
		{
			std::cout << "Yaffut " << version << std::endl;
			return 0;
		}

		#if defined(__GNUC__) && !defined(_WIN32)
		std::cout << "pid(" << getpid() << ")" << std::endl;
		#endif

		const char* all[] = {"All"};
		const char** test = all;
		int num = 1;
		if(1 < argc)
		{
			test = argv;
			num = argc;
		}
    
		for(int i = 0; i < num; ++i)
		{
			try
			{
				std::istringstream is(test[i]);
				int num;
				is >> num;
				if(is)
				{
					if(num < int(m_Tests.size()))
					{
						Tests_t::const_iterator it = m_Tests.begin();
						while(0 <= --num)
						{
							++it;
						}
						Factory::Instance().Run(it->first);
					}
				}
				else
				{
					Factory::Instance().Run(test[i]);
				}
			}
			catch(const std::exception& e)
			{			
				std::clog << e.what() << std::endl;
			}
		}

		Factory::Instance().Report ();
		return (int)Factory::Instance().Fail ();
	}

}//yaffut
