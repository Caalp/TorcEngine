
#include <catch2/catch_all.hpp>

#include "TestList.h"


int main(int argc, char* argv[])
{

	Catch::Session session; // There must be exactly one instance

	/*
	int height = 0; // Some user variable you want to be able to set

	
	// Build a new parser on top of Catch2's
	using namespace Catch::Clara;
	auto cli
		= session.cli()           // Get Catch2's command line parser
		| Opt(height, "height") // bind variable to a new option, with a hint string
		["-g"]["--height"]    // the option names it will respond to
		("how high?");        // description string for the help output

	// Now pass the new composite back to Catch2 so it uses that
	session.cli(cli);
	*/

	// Let Catch2 (using Clara) parse the command line
	int returnCode = session.applyCommandLine(argc, argv);
	if (returnCode != 0) // Indicates a command line error
		return returnCode;

	/*
	// if set on the command line then 'height' is now set at this point
	if (height > 0)
		std::cout << "height: " << height << std::endl;
	*/

	return session.run();
	

	return 0;
}
