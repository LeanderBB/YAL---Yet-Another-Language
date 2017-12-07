/* Generated by re2c 1.0.2 on Mon Dec  4 23:25:20 2017 */
/*
 *  Copyright 2017 by Leander Beernaert (leanderbb@gmail.com)
 *
 *  This file is part of YAL.
 *
 *  YAL is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3
 *  of the License, or (at your option) any later version.
 *
 *  YAL is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with YAL. If not, see <http://www.gnu.org/licenses/>.
 */
#include "yal/yal.h"
#include "yal/io/memorystream.h"
#include "yal/lexer/tokens.h"
#include "yal/lexer/lexer.h"
#include <iostream>
#define YYMAXFILL 7


namespace yal {

    enum {
        kMaxBufferSize = 4096
    };

    struct Lexer::LexerState {
        uint8_t buffer[kMaxBufferSize + YYMAXFILL];
        uint8_t* limit = nullptr;
        uint8_t* current = nullptr;
        uint8_t* marker = nullptr;
        uint8_t* token = nullptr;
        size_t lineNum = 1;
        size_t streamReadOffset = std::numeric_limits<size_t>::max();
        size_t lineStartOffset = 0;
        size_t tokenLineStart =0;
        size_t tokenColumnStart = 0;
        bool eof = false;

        bool fill(const size_t size,
                  ByteStream& stream) {

            if (eof) {
                return false;
            }
            const size_t free = token - buffer;
            if (free < size) {
                return false;
            }
            streamReadOffset = static_cast<uintptr_t>(limit - token) + stream.getPosition();
            ::memmove(buffer, token, limit - token);
            limit -= free;
            current -= free;
            marker -= free;
            token -= free;
            limit += stream.read(limit, free);
            if (limit < buffer + kMaxBufferSize) {
                eof = true;
                memset(limit, 0, YYMAXFILL);
                limit += YYMAXFILL;
            }
            return true;
        }


        size_t getColumnOffsetStart() const {
            if ( streamReadOffset== std::numeric_limits<size_t>::max()) {
                return 1;
            }

            const size_t bufferOffset  = getBufferOffsetTokBegin();
            return streamReadOffset + bufferOffset - lineStartOffset + 1;
        }

        size_t getColumnOffsetEnd() const {

            const size_t bufferOffset  =getBufferOffsetTokEnd();

            return streamReadOffset  + bufferOffset - lineStartOffset;
        }

        size_t getStreamOffset() const {
            const size_t bufferOffset  = getBufferOffsetTokBegin();
            return streamReadOffset + bufferOffset;
        }

        size_t getBufferOffsetTokBegin() const {
            const size_t bufferOffset =
                    static_cast<size_t>(reinterpret_cast<uintptr_t>(token)
                                        - reinterpret_cast<uintptr_t>(buffer));
            return bufferOffset;
        }

        size_t getBufferOffsetTokEnd() const {
            const size_t bufferOffset =
                    static_cast<size_t>(reinterpret_cast<uintptr_t>(current)
                                        - reinterpret_cast<uintptr_t>(buffer));
            return bufferOffset;
        }


        void updateLineStartOffset() {
            lineNum++;
            const size_t bufferOffset  = getBufferOffsetTokEnd();
            lineStartOffset = streamReadOffset + bufferOffset;
        }

        void markScanBegin() {
            token = current;
            tokenLineStart = lineNum;
            tokenColumnStart = getColumnOffsetStart();
        }

        size_t getTokenLength() const {
            return  static_cast<size_t>(reinterpret_cast<uintptr_t>(current)
                                        - reinterpret_cast<uintptr_t>(token));
        }

    };

    Lexer::Lexer(MemoryStream &stream):
        m_stream(stream),
        m_lexerState(createLexerState()),
        m_curToken()
    {
        m_lexerState->limit = m_lexerState->buffer + kMaxBufferSize;
        m_lexerState->current = m_lexerState->limit;
        m_lexerState->token =m_lexerState->limit;
        m_lexerState->marker = m_lexerState->limit;
        m_curToken.token = Token::TokenCount;
    }

    Lexer::~Lexer(){

    }

    void
    Lexer::setToken(const Token token,
                    const LexerState& state) {
        m_curToken.token = token;
        m_curToken.lineStart = state.tokenLineStart;
        m_curToken.lineEnd = state.lineNum;
        m_curToken.columnStart = state.tokenColumnStart;
        m_curToken.columnEnd =state.getColumnOffsetEnd();
        m_curToken.tokenOffsetInStream = state.getStreamOffset();
        const char* streamStr =
                static_cast<const char*>(m_stream.getPtrAt(m_curToken.tokenOffsetInStream));
        m_curToken.tokenStr = StringRefPod{streamStr, state.getTokenLength()};
    }

    void
    Lexer::setLexerError(const LexerState& state) {
        m_curToken.token = Token::TokenCount;
        m_curToken.lineStart = state.tokenLineStart;
        m_curToken.lineEnd = m_curToken.lineEnd;
        m_curToken.columnStart = state.tokenColumnStart;
        m_curToken.columnEnd = m_curToken.columnStart;
        m_curToken.tokenOffsetInStream = state.getStreamOffset();
    }

    std::unique_ptr<Lexer::LexerState>
    Lexer::createLexerState(){
        return std::make_unique<Lexer::LexerState>();
    }

    Lexer::Status
    Lexer::re2cExecute() {
        for (;;) {
            m_lexerState->markScanBegin();
            
{
	unsigned char yych;
	if ((m_lexerState->limit - m_lexerState->current) < 7) if (!m_lexerState->fill(7, m_stream)) return Status::EOS;
	yych = *m_lexerState->current;
	switch (yych) {
	case 0x00:	goto yy2;
	case '\t':
	case ' ':	goto yy6;
	case '\n':	goto yy9;
	case '!':	goto yy11;
	case '&':	goto yy12;
	case '(':	goto yy14;
	case ')':	goto yy16;
	case '*':	goto yy18;
	case '+':	goto yy20;
	case ',':	goto yy22;
	case '-':	goto yy24;
	case '.':	goto yy26;
	case '/':	goto yy28;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy30;
	case ':':	goto yy33;
	case ';':	goto yy35;
	case '<':	goto yy37;
	case '=':	goto yy39;
	case '>':	goto yy41;
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'c':
	case 'e':
	case 'g':
	case 'h':
	case 'j':
	case 'k':
	case 'p':
	case 'q':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	case '[':	goto yy46;
	case ']':	goto yy48;
	case 'a':	goto yy50;
	case 'b':	goto yy51;
	case 'd':	goto yy52;
	case 'f':	goto yy53;
	case 'i':	goto yy54;
	case 'l':	goto yy55;
	case 'm':	goto yy56;
	case 'n':	goto yy57;
	case 'o':	goto yy58;
	case 'r':	goto yy59;
	case 's':	goto yy60;
	case 't':	goto yy61;
	case 'u':	goto yy62;
	case 'v':	goto yy63;
	case '{':	goto yy64;
	case '}':	goto yy66;
	default:	goto yy4;
	}
yy2:
	++m_lexerState->current;
	{ if (m_lexerState->limit - m_lexerState->token == YYMAXFILL) {return Status::EOS;} }
yy4:
	++m_lexerState->current;
yy5:
	{ setToken(Token::TokenCount, *m_lexerState); return Status::Error;}
yy6:
	++m_lexerState->current;
	if (m_lexerState->limit <= m_lexerState->current) if (!m_lexerState->fill(1, m_stream)) return Status::EOS;
	yych = *m_lexerState->current;
	switch (yych) {
	case '\t':
	case ' ':	goto yy6;
	default:	goto yy8;
	}
yy8:
	{continue;}
yy9:
	++m_lexerState->current;
	{m_lexerState->updateLineStartOffset(); continue;}
yy11:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '=':	goto yy68;
	default:	goto yy5;
	}
yy12:
	++m_lexerState->current;
	{ setToken(Token::Reference, *m_lexerState); return Status::Ok;}
yy14:
	++m_lexerState->current;
	{ setToken(Token::BeginPar, *m_lexerState); return Status::Ok;}
yy16:
	++m_lexerState->current;
	{ setToken(Token::EndPar, *m_lexerState); return Status::Ok;}
yy18:
	++m_lexerState->current;
	{ setToken(Token::Mult, *m_lexerState); return Status::Ok;}
yy20:
	++m_lexerState->current;
	{ setToken(Token::Plus, *m_lexerState); return Status::Ok;}
yy22:
	++m_lexerState->current;
	{ setToken(Token::Comma, *m_lexerState); return Status::Ok;}
yy24:
	++m_lexerState->current;
	{ setToken(Token::Minus, *m_lexerState); return Status::Ok;}
yy26:
	++m_lexerState->current;
	{ setToken(Token::Dot, *m_lexerState); return Status::Ok;}
yy28:
	++m_lexerState->current;
	{ setToken(Token::Div, *m_lexerState); return Status::Ok;}
yy30:
	m_lexerState->marker = ++m_lexerState->current;
	if ((m_lexerState->limit - m_lexerState->current) < 2) if (!m_lexerState->fill(2, m_stream)) return Status::EOS;
	yych = *m_lexerState->current;
	switch (yych) {
	case '.':	goto yy70;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy30;
	default:	goto yy32;
	}
yy32:
	{ setToken(Token::IntegerLiteral, *m_lexerState); return Status::Ok;}
yy33:
	++m_lexerState->current;
	{ setToken(Token::Colon, *m_lexerState); return Status::Ok;}
yy35:
	++m_lexerState->current;
	{ setToken(Token::SemiColon, *m_lexerState); return Status::Ok;}
yy37:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '=':	goto yy72;
	default:	goto yy38;
	}
yy38:
	{ setToken(Token::CompareLt, *m_lexerState); return Status::Ok;}
yy39:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '=':	goto yy74;
	default:	goto yy40;
	}
yy40:
	{ setToken(Token::Assign, *m_lexerState); return Status::Ok;}
yy41:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '=':	goto yy76;
	default:	goto yy42;
	}
yy42:
	{ setToken(Token::CompareGt, *m_lexerState); return Status::Ok;}
yy43:
	++m_lexerState->current;
	if (m_lexerState->limit <= m_lexerState->current) if (!m_lexerState->fill(1, m_stream)) return Status::EOS;
	yych = *m_lexerState->current;
yy44:
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy45;
	}
yy45:
	{ setToken(Token::Identifier, *m_lexerState); return Status::Ok;}
yy46:
	++m_lexerState->current;
	{ setToken(Token::BeginArray, *m_lexerState); return Status::Ok;}
yy48:
	++m_lexerState->current;
	{ setToken(Token::EndArray, *m_lexerState); return Status::Ok;}
yy50:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'n':	goto yy78;
	default:	goto yy44;
	}
yy51:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'o':	goto yy79;
	default:	goto yy44;
	}
yy52:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'o':	goto yy80;
	default:	goto yy44;
	}
yy53:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'a':	goto yy81;
	case 'l':	goto yy82;
	case 'n':	goto yy83;
	default:	goto yy44;
	}
yy54:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '1':	goto yy85;
	case '3':	goto yy86;
	case '8':	goto yy87;
	default:	goto yy44;
	}
yy55:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'e':	goto yy89;
	default:	goto yy44;
	}
yy56:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'o':	goto yy90;
	case 'u':	goto yy91;
	default:	goto yy44;
	}
yy57:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'o':	goto yy92;
	default:	goto yy44;
	}
yy58:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'r':	goto yy93;
	default:	goto yy44;
	}
yy59:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'e':	goto yy95;
	default:	goto yy44;
	}
yy60:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'e':	goto yy96;
	case 't':	goto yy97;
	default:	goto yy44;
	}
yy61:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'h':	goto yy98;
	case 'r':	goto yy99;
	case 'y':	goto yy100;
	default:	goto yy44;
	}
yy62:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '1':	goto yy101;
	case '3':	goto yy102;
	case '8':	goto yy103;
	default:	goto yy44;
	}
yy63:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'a':	goto yy105;
	default:	goto yy44;
	}
yy64:
	++m_lexerState->current;
	{ setToken(Token::BeginScope, *m_lexerState); return Status::Ok;}
yy66:
	++m_lexerState->current;
	{ setToken(Token::EndScope, *m_lexerState); return Status::Ok;}
yy68:
	++m_lexerState->current;
	{ setToken(Token::CompareNe, *m_lexerState); return Status::Ok;}
yy70:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy106;
	default:	goto yy71;
	}
yy71:
	m_lexerState->current = m_lexerState->marker;
	goto yy32;
yy72:
	++m_lexerState->current;
	{ setToken(Token::CompareLe, *m_lexerState); return Status::Ok;}
yy74:
	++m_lexerState->current;
	{ setToken(Token::CompareEq, *m_lexerState); return Status::Ok;}
yy76:
	++m_lexerState->current;
	{ setToken(Token::CompareGe, *m_lexerState); return Status::Ok;}
yy78:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'd':	goto yy109;
	default:	goto yy44;
	}
yy79:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'o':	goto yy111;
	default:	goto yy44;
	}
yy80:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'u':	goto yy112;
	default:	goto yy44;
	}
yy81:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'l':	goto yy113;
	default:	goto yy44;
	}
yy82:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'o':	goto yy114;
	default:	goto yy44;
	}
yy83:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy84;
	}
yy84:
	{ setToken(Token::Function, *m_lexerState);return Status::Ok; }
yy85:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '6':	goto yy115;
	default:	goto yy44;
	}
yy86:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '2':	goto yy117;
	default:	goto yy44;
	}
yy87:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy88;
	}
yy88:
	{ setToken(Token::TypeInt8, *m_lexerState); return Status::Ok;}
yy89:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 't':	goto yy119;
	default:	goto yy44;
	}
yy90:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'd':	goto yy121;
	default:	goto yy44;
	}
yy91:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 't':	goto yy123;
	default:	goto yy44;
	}
yy92:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 't':	goto yy125;
	default:	goto yy44;
	}
yy93:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy94;
	}
yy94:
	{ setToken(Token::Or, *m_lexerState); return Status::Ok; }
yy95:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 't':	goto yy127;
	default:	goto yy44;
	}
yy96:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'l':	goto yy128;
	default:	goto yy44;
	}
yy97:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'r':	goto yy129;
	default:	goto yy44;
	}
yy98:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'i':	goto yy130;
	default:	goto yy44;
	}
yy99:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'u':	goto yy131;
	default:	goto yy44;
	}
yy100:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'p':	goto yy132;
	default:	goto yy44;
	}
yy101:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '6':	goto yy133;
	default:	goto yy44;
	}
yy102:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '2':	goto yy135;
	default:	goto yy44;
	}
yy103:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy104;
	}
yy104:
	{ setToken(Token::TypeUInt8, *m_lexerState); return Status::Ok;}
yy105:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'r':	goto yy137;
	default:	goto yy44;
	}
yy106:
	++m_lexerState->current;
	if (m_lexerState->limit <= m_lexerState->current) if (!m_lexerState->fill(1, m_stream)) return Status::EOS;
	yych = *m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy106;
	default:	goto yy108;
	}
yy108:
	{ setToken(Token::DecimalLiteral, *m_lexerState); return Status::Ok;}
yy109:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy110;
	}
yy110:
	{ setToken(Token::And, *m_lexerState); return Status::Ok; }
yy111:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'l':	goto yy139;
	default:	goto yy44;
	}
yy112:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'b':	goto yy141;
	default:	goto yy44;
	}
yy113:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 's':	goto yy142;
	default:	goto yy44;
	}
yy114:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'a':	goto yy143;
	default:	goto yy44;
	}
yy115:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy116;
	}
yy116:
	{ setToken(Token::TypeInt16, *m_lexerState); return Status::Ok;}
yy117:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy118;
	}
yy118:
	{ setToken(Token::TypeInt32, *m_lexerState); return Status::Ok;}
yy119:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy120;
	}
yy120:
	{ setToken(Token::Let, *m_lexerState);return Status::Ok; }
yy121:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy122;
	}
yy122:
	{ setToken(Token::Mod, *m_lexerState); return Status::Ok;}
yy123:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy124;
	}
yy124:
	{ setToken(Token::Mutable, *m_lexerState); return Status::Ok;}
yy125:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy126;
	}
yy126:
	{ setToken(Token::Not, *m_lexerState); return Status::Ok; }
yy127:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'u':	goto yy144;
	default:	goto yy44;
	}
yy128:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'f':	goto yy145;
	default:	goto yy44;
	}
yy129:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'u':	goto yy147;
	default:	goto yy44;
	}
yy130:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 's':	goto yy148;
	default:	goto yy44;
	}
yy131:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'e':	goto yy150;
	default:	goto yy44;
	}
yy132:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'e':	goto yy152;
	default:	goto yy44;
	}
yy133:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy134;
	}
yy134:
	{ setToken(Token::TypeUInt16, *m_lexerState); return Status::Ok;}
yy135:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy136;
	}
yy136:
	{ setToken(Token::TypeUInt32, *m_lexerState); return Status::Ok;}
yy137:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy138;
	}
yy138:
	{ setToken(Token::Var, *m_lexerState); return Status::Ok; }
yy139:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy140;
	}
yy140:
	{ setToken(Token::TypeBool, *m_lexerState); return Status::Ok;}
yy141:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'l':	goto yy154;
	default:	goto yy44;
	}
yy142:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'e':	goto yy155;
	default:	goto yy44;
	}
yy143:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 't':	goto yy157;
	default:	goto yy44;
	}
yy144:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'r':	goto yy159;
	default:	goto yy44;
	}
yy145:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy146;
	}
yy146:
	{ setToken(Token::Self, *m_lexerState);return Status::Ok; }
yy147:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'c':	goto yy160;
	default:	goto yy44;
	}
yy148:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy149;
	}
yy149:
	{ setToken(Token::This, *m_lexerState);return Status::Ok; }
yy150:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy151;
	}
yy151:
	{ setToken(Token::True, *m_lexerState); return Status::Ok; }
yy152:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy153;
	}
yy153:
	{ setToken(Token::Type, *m_lexerState); return Status::Ok;}
yy154:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'e':	goto yy161;
	default:	goto yy44;
	}
yy155:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy156;
	}
yy156:
	{ setToken(Token::False, *m_lexerState); return Status::Ok; }
yy157:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy158;
	}
yy158:
	{ setToken(Token::TypeFloat, *m_lexerState); return Status::Ok;}
yy159:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 'n':	goto yy163;
	default:	goto yy44;
	}
yy160:
	yych = *++m_lexerState->current;
	switch (yych) {
	case 't':	goto yy165;
	default:	goto yy44;
	}
yy161:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy162;
	}
yy162:
	{ setToken(Token::TypeDouble, *m_lexerState); return Status::Ok;}
yy163:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy164;
	}
yy164:
	{ setToken(Token::Return, *m_lexerState);return Status::Ok; }
yy165:
	yych = *++m_lexerState->current;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy43;
	default:	goto yy166;
	}
yy166:
	{ setToken(Token::Struct, *m_lexerState); return Status::Ok;}
}

        }

    }
}
