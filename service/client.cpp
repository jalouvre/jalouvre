/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the Alpine Toolkit software.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** $ALPINE_TOOLKIT_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include "service/client.h"
#include "alpine_toolkit.h"

#include <QtDebug>

#ifdef ANDROID
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#include <QtAndroid>
#endif

#include "service/definitions.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

ServiceClient::ServiceClient(QObject * parent)
  : QObject(parent),
    m_started(false),
    m_node()
{}

ServiceClient::~ServiceClient()
{}

#ifdef ANDROID
void
ServiceClient::call_service_static_method(const char * method)
{
  QAndroidJniObject::callStaticMethod<void>("org/alpine_toolkit/AlpineToolkitService",
                                            method,
                                            "(Landroid/content/Context;)V",
                                            QtAndroid::androidActivity().object());
}
#else
QProcess * ServiceClient::m_service_process = nullptr;
#endif

void
ServiceClient::start_service()
{
  if (m_started)
    return;

  qATInfo() << "Start Alpine Toolkit Service";
#ifdef ANDROID
  call_service_static_method("start_service");
#else
    m_service_process = new QProcess(this);
    m_service_process->start(QStringLiteral("alpine-toolkit-service"));
    // Fixme: connect to signals
#endif
  qATInfo() << "Connect to Alpine Toolkit Service";
  connect();
  // init_connections();
  set_service_state(true);

// 04-10 18:24:32.435  I Alpine Toolkit: ../alpine-toolkit/service/client.cpp:68 (void ServiceClient::start_service()): Start Alpine Toolkit Service
// 04-10 18:24:32.455  I ActivityManager: Start proc 28256:org.alpine_toolkit:qt/u0a199 for service org.alpine_toolkit/.AlpineToolkitService
// 04-10 18:24:32.455  I Alpine Toolkit: ../alpine-toolkit/service/client.cpp:70 (void ServiceClient::start_service()): Connect to Alpine Toolkit Service
// 04-10 18:24:32.535  I AlpineToolkitService: onCreate
// 04-10 18:24:32.885  I AlpineToolkitService: onStartCommand null
// 04-10 18:24:32.885  I         : ../../alpine-toolkit/service/main.cpp:42 (int main(int, char**)): Start Apline Tookit Service
// 04-10 18:24:32.895 28256 28269 I libservice.so: ../../alpine-toolkit/service/service.cpp:41 (Service::Service(QObject*)): Alpine Toolkit Service Source is started
}

void
ServiceClient::stop_service()
{
  if (not m_started)
    return;

  qATInfo() << "Stop Alpine Toolkit Service";
#ifdef ANDROID
  call_service_static_method("stop_service");
#else
  m_service_process->close();
#endif
  // Fixme: disconnect
  m_replica.clear();
  set_service_state(false);
}

void
ServiceClient::connect()
{
  bool rc;
  rc = m_node.connectToNode(QUrl(QStringLiteral(SERVICE_URL)));
  if (!rc)
    qATCritical() << "Coundn't connect to service";

  m_replica.reset(m_node.acquire<ServiceReplica>());

  // Blocking call
  // Fixme: use stateChanged signal else it blocks ui
  int timeout = 30 * 1000; // ms
  rc = m_replica->waitForSource(timeout);
  if (!rc)
    qATCritical() << "Coundn't acquire service replica";
  // Q_ASSERT(res);
}

void
ServiceClient::init_connections()
{
  qATInfo() << "connect signals";
  // We can connect to signals/slots directly because our replica was generated by repc.
  QObject::connect(m_replica.data(), SIGNAL(pong()), this, SLOT(on_pong()));
}

void
ServiceClient::set_service_state(bool state)
{
  if (m_started != state) {
    m_started = state;
    emit serviceStateChanged(state);
  }
}

void
ServiceClient::on_pong()
{
  qATInfo() << "Received pong";
}

void
ServiceClient::foo()
{
  init_connections();
}

// QC_END_NAMESPACE
