/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2006
 *
 *  Last modified:
 *     $Date: 2013-07-11 12:30:18 +0200 (Thu, 11 Jul 2013) $ by $Author: schulte $
 *     $Revision: 13840 $
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <gecode/search.hh>

namespace Gecode { namespace Search {

  /*
   * Stopping for node limit
   *
   */
  bool
  NodeStop::stop(const Statistics& s, const Options&) {
    return s.node > l;
  }


  /*
   * Stopping for failure limit
   *
   */
  bool
  FailStop::stop(const Statistics& s, const Options&) {
    return s.fail > l;
  }


  /*
   * Stopping for time limit
   *
   */
  bool
  TimeStop::stop(const Statistics&, const Options&) {
    return t.stop() > l;
  }


  /*
   * Stopping for meta search engines
   *
   */

  bool 
  MetaStop::stop(const Statistics& s, const Options& o) {
    // Stop if the fail stop object for the engine says so
    if (e_stop->stop(s,o)) {
      e_stopped = true;
      m_stat.restart++;
      return true;
    }
    // Stop if the stop object for the meta engine says so
    if ((m_stop != NULL) && m_stop->stop(m_stat+s,o)) {
      e_stopped = false;
      return true;
    }
    return false;
  }

}}

// STATISTICS: search-other
