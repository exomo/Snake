#ifndef UTF8STREAM_H_INCLUDED
#define UTF8STREAM_H_INCLUDED

#include "stxutif.h"

/**
 * Hier sind ein paar Hilfsfunktionen definiert, mit denen das Lesen und Schreiben von Dateien
 * in UTF-8 Kodierung erm�glichen. Dazu wird Code aus folgendem Artikel verwendet (im Header "stxutif.h"):
 * http://www.codeproject.com/Articles/38242/Reading-UTF-with-C-streams
 */
namespace ExomoSnake
{
    /**
     * �ffne einen Eingabe-filestream f�r eine Datei und wende die UTF8 konvertierung darauf an.
     * Liest auch den BOM und �berpr�ft daran ob die Datei wirklich UTF8 kodiert ist.
     */
    void inline openUtf8ForReading(std::wifstream& stream, std::string filename);

    /**
     * �ffne einen Ausgabe-filestream f�r eine Datei und wende die UTF8 konvertierung darauf an.
     * Schreibt auch den BOM.
     */
    void inline openUtf8ForWriting(std::wofstream& stream, std::string filename);

}

#endif // UTF8STREAM_H_INCLUDED
