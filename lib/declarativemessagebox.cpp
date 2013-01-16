/*
  Copyright (C) 2012 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, krake@kdab.com
  Author: Tobias Koenig, tokoe@kdab.com

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include "declarativemessagebox_p.h"

class DeclarativeMessageBoxAttached::Private
{
  public:
    Private() : buttons(QMessageBox::Ok), defaultButton(QMessageBox::NoButton) {}

  public:
    QMessageBox::StandardButtons buttons;
    QMessageBox::StandardButton defaultButton;
};

DeclarativeMessageBoxAttached::DeclarativeMessageBoxAttached(QObject *parent)
  : StaticDialogMethodAttached(parent), d(new Private)
{
}

DeclarativeMessageBoxAttached::~DeclarativeMessageBoxAttached()
{
  delete d;
}

void DeclarativeMessageBoxAttached::setButtons(int buttons)
{
  if (d->buttons == buttons)
    return;

  d->buttons = static_cast<QMessageBox::StandardButtons>(buttons);
  emit buttonsChanged(buttons);
}

int DeclarativeMessageBoxAttached::buttons() const
{
  return d->buttons;
}

void DeclarativeMessageBoxAttached::setDefaultButton(int defaultButton)
{
  if (d->defaultButton == defaultButton)
    return;

  d->defaultButton = static_cast<QMessageBox::StandardButton>(defaultButton);
  emit defaultButtonChanged(defaultButton);
}

int DeclarativeMessageBoxAttached::defaultButton() const
{
  return d->defaultButton;
}

void DeclarativeMessageBoxAttached::about(const QString &title, const QString &text)
{
  QMessageBox::about(bestParentWindow(), title, text);
}

void DeclarativeMessageBoxAttached::aboutQt()
{
  QMessageBox::aboutQt(bestParentWindow());
}

void DeclarativeMessageBoxAttached::aboutQt(const QString &title)
{
  QMessageBox::aboutQt(bestParentWindow(), title);
}

int DeclarativeMessageBoxAttached::critical(const QString &title, const QString &text)
{
  return QMessageBox::critical(bestParentWindow(), title, text, d->buttons, d->defaultButton);
}

int DeclarativeMessageBoxAttached::information(const QString &title, const QString &text)
{
  return QMessageBox::information(bestParentWindow(), title, text, d->buttons, d->defaultButton);
}

int DeclarativeMessageBoxAttached::question(const QString &title, const QString &text)
{
  return QMessageBox::question(bestParentWindow(), title, text, d->buttons, d->defaultButton);
}

int DeclarativeMessageBoxAttached::warning(const QString &title, const QString &text)
{
  return QMessageBox::warning(bestParentWindow(), title, text, d->buttons, d->defaultButton);
}

Q_DECLARE_METATYPE(Qt::WindowFlags)

DeclarativeMessageBox::DeclarativeMessageBox(QWidget *parent) : QMessageBox(parent)
{
  setProperty("originalWindowFlags", QVariant::fromValue(windowFlags()));
}

DeclarativeMessageBoxAttached *DeclarativeMessageBox::qmlAttachedProperties(QObject *parent)
{
  return new DeclarativeMessageBoxAttached(parent);
}
