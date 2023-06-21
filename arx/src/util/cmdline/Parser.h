/*
 * Copyright 2013 Arx Libertatis Team (see the AUTHORS file)
 *
 * This file is part of Arx Libertatis.
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef ARX_UTIL_CMDLINE_PARSER_H
#define ARX_UTIL_CMDLINE_PARSER_H

#include <string>

#include "util/cmdline/Interpreter.h"

namespace util { namespace cmdline {

/*!
 * Parse the command-line arguments in argv into the options specified by the
 * given interpreter
 *
 * The command-line syntax consists of three different option types:
 *
 * <b>Long options:</b> \code--option\endcode
 *
 *   This is the default form of options and consists of two dashes followed by
 *   one or more characters. Any character except for the \c = sign is supported,
 *   but it is suggested to only use alpha-numeric letters and dashes.
 *
 *   Long options can have required and optional arguments. For options with \c n
 *   required the following \c n command-line tokens will will always be interpreted
 *   as arguments to the option, even if they start with a dash.
 *
 *   Optional arguments will only be considered until the next token starting with
 *   a dash. To force a token to be treated as an (optional) argument the
 *   \code--option=argument\endcode syntax is supported.
 *
 * <b>Short options:</b> \code-o\endcode
 *
 *   Short options are a convenience alias of the long options. Sort options
 *   can be any single character except for the dash. Mandatory and optional arguments
 *   following the option in separate tokens are handled in exactly the same way.
 *
 *   Short options support the \code-oargument\endcode syntax to force a token to be
 *   treated as an argument.
 *
 *   Multiple short options can be combined into a single token with the restriction
 *   that only the last option takes any arguments. If options \code-a\endcode and
 *   \code-b\endcode don't take any arguments, but \code-c\endcode does, then
 *   \code-abcargument\endcode is equivalent to \code-a -b -cargument\endcode.
 *
 * <b>Positional arguments:</b>
 *
 *   Positional arguments are everything else: tokens that don't start with a dash
 *   \b and are not consumed as arguments to any options. They are passed to the \c --
 *   option in @param cli.
 *
 *   The special \code--\endcode token can be used to force all following command-line
 *   tokens to be treated as positional arguments, even if they start with a dash.
 *
 * @param cli  An @ref interpreter<std::string> specifying which options are available
 * @param argc Number of entries in argv
 * @param argv Array of command-line tokens - first one will be ignored
 *
 * @throws error If there was a syntax error or unknown options in the command-line.
 *               @ref error::what will contain a user-friendly error message.
 */
void parse(interpreter<std::string> & cli, int argc, char ** argv);

} } // namespace util::cmdline

#endif // ARX_UTIL_CMDLINE_PARSER_H
