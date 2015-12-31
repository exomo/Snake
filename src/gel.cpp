#include "stxutif.h"
#include "utf8stream.h"

#include <fstream>

namespace gel
{namespace stdx
{
	//instantiate the global locale
	std::locale utf8_locale(std::locale(), new utf8cvt<true>);

}}

// Hilfsfunktionen um einen Filestream für UTF8 ein/ausgabe zu öffnen
namespace ExomoSnake
{
    void openUtf8ForReading(std::wifstream& stream, std::string filename)
    {
        stream.open(filename);
        stream.imbue(gel::stdx::utf8_locale);
        wchar_t BOM;
        stream.read(&BOM,1);
        if(BOM != 0xFEFF)
        {
            throw std::runtime_error("Bad Byte Order Mark");
        }
    }

    void openUtf8ForWriting(std::wofstream& stream, std::string filename)
    {
        stream.open(filename);
        stream.imbue(gel::stdx::utf8_locale);
        wchar_t BOM = 0xFEFF;
        stream.write(&BOM,1);
    }

}
