/******************************************************************************
 *  Copyright (C) 2013 – 2020 by David Baum <david.baum@naraesk.eu>           *
 *                                                                            *
 *  This library is free software; you can redistribute it and/or modify      *
 *  it under the terms of the GNU Lesser General Public License as published  *
 *  by the Free Software Foundation; either version 2 of the License or (at   *
 *  your option) any later version.                                           *
 *                                                                            *
 *  This library is distributed in the hope that it will be useful,           *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 *  Library General Public License for more details.                          *
 *                                                                            *
 *  You should have received a copy of the GNU Lesser General Public License  *
 *  along with this library; see the file COPYING.LIB.                        *
 *  If not, see <http://www.gnu.org/licenses/>.                               *
 *****************************************************************************/

#include "Bing.h"
#include "translateShellProcess.h"

Bing::Bing(Plasma::AbstractRunner *runner, QAction * action)
        : m_runner(runner), m_action(action) {
}

Plasma::QueryMatch Bing::translate(const QString &text, const QPair<QString, QString> &language) {
    TranslateShellProcess process("bing");
    QString result = process.translate(language, text);
    Plasma::QueryMatch match(m_runner);
    if(result == "\n") { // empty result
        match.setType(Plasma::QueryMatch::NoMatch);
    } else {
        match.setData("audio");
        match.setType(Plasma::QueryMatch::ExactMatch);
        match.setIcon(QIcon::fromTheme("applications-education-language"));
        match.setText(result);
        match.setSubtext("Bing");
        match.setRelevance(1);
        match.setSelectedAction(m_action);
    }
    return match;
}

Bing::~Bing() = default;
