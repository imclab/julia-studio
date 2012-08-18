/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2012 AudioCodes Ltd.
**
** Author: Orgad Shaneh <orgad.shaneh@audiocodes.com>
**
** Contact: http://www.qt-project.org/
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**************************************************************************/

#ifndef CLEARCASESUBMITEDITOR_H
#define CLEARCASESUBMITEDITOR_H

#include <QPair>
#include <QStringList>

#include <vcsbase/vcsbasesubmiteditor.h>

namespace ClearCase {
namespace Internal {

class ClearCaseSubmitEditorWidget;

class ClearCaseSubmitEditor : public VcsBase::VcsBaseSubmitEditor
{
    Q_OBJECT
public:
    explicit ClearCaseSubmitEditor(const VcsBase::VcsBaseSubmitEditorParameters *parameters,
                                   QWidget *parentWidget = 0);

    static QString fileFromStatusLine(const QString &statusLine);

    void setStatusList(const QStringList &statusOutput);
    ClearCaseSubmitEditorWidget *submitEditorWidget();

protected:
    virtual QByteArray fileContents() const;
};

} // namespace Internal
} // namespace ClearCase

#endif // CLEARCASESUBMITEDITOR_H