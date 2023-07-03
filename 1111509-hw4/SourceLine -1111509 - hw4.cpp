// SourceLine class member-function definitions.

#include <iostream>
using std::cout;

#include "SourceLine.h" // SourceLine class definition

// default/conversion constructor
SourceLine::SourceLine()
   : sourceLine()
{
}

SourceLine& SourceLine::operator=( const char * const ptr )
{
   sourceLine = ptr;
   return *this;
}

void SourceLine::delComments()
{
	size_t length = sourceLine.size();
	if (length > 1) {
		for (size_t i = 0; i < length - 1; i++) {
			if (sourceLine[i] == '/' && sourceLine[i + 1] == '/') {
				sourceLine.erase(i, length - i);
				break;
			}
		}
	}
	
}

void SourceLine::delStrConst()
{
	size_t length = sourceLine.size();
	if (length > 1) {
		while(sourceLine.find('"') != npos) {
			size_t i = sourceLine.find('"');
			size_t j = i + 1;
			while (sourceLine[j] != '"') {
				if (sourceLine[j] == '\\')
					j++;

				j++;
			}
			sourceLine.erase(i, j - i + 1);
		}	
		
	}

}

void SourceLine::delCharConst()
{
	size_t length = sourceLine.size();
	if (length > 1) {
		while (sourceLine.find('\'') != npos) {
			size_t i = sourceLine.find('\'');
			size_t j = i + 1;
			while (sourceLine[j] != '\'') {
				if (sourceLine[j] == '\\')
					j++;

				j++;
			}
			sourceLine.erase(i, j - i + 1);
		}
	}

}

void SourceLine::extractIdentifiers( vector< Identifier > &identifiers )
{
	size_t length = sourceLine.size();
	for (size_t i = 0; i < length; i++) {
		if (isalpha(sourceLine[i]) || sourceLine[i] == '_') {
			int j = i + 1;
			while (isalnum(sourceLine[j]) || sourceLine[j] == '_')
				j++;
			
			Identifier temp(sourceLine.substr(i, j - i));
			identifiers.push_back(temp);
			
			i = j;
		}
		
	}

}

bool operator==( const SourceLine &lhs, const SourceLine &rhs )
{
   return lhs.sourceLine == rhs.sourceLine;
}

bool operator!=( const SourceLine &lhs, const SourceLine &rhs )
{
   return !( lhs == rhs );
}