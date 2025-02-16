/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
 * Copyright 2018-2020 SChernykh   <https://github.com/SChernykh>
 * Copyright 2016-2020 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include "base/net/stratum/strategies/SinglePoolStrategy.h"
#include "3rdparty/rapidjson/document.h"
#include "base/kernel/interfaces/IClient.h"
#include "base/kernel/interfaces/IStrategyListener.h"
#include "base/kernel/Platform.h"
#include "base/net/stratum/Pool.h"


uvloop::SinglePoolStrategy::SinglePoolStrategy(const Pool &pool, int retryPause, int retries, IStrategyListener *listener, bool quiet) :
    m_active(false),
    m_listener(listener)
{
    m_client = pool.createClient(0, this);
    m_client->setRetries(retries);
    m_client->setRetryPause(retryPause * 1000);
    m_client->setQuiet(quiet);
}


uvloop::SinglePoolStrategy::~SinglePoolStrategy()
{
    m_client->deleteLater();
}


int64_t uvloop::SinglePoolStrategy::submit(const JobResult &result)
{
    return m_client->submit(result);
}


void uvloop::SinglePoolStrategy::connect()
{
    m_client->connect();
}


void uvloop::SinglePoolStrategy::resume()
{
    if (!isActive()) {
        return;
    }

    m_listener->onJob(this, m_client, m_client->job(), rapidjson::Value(rapidjson::kNullType));
}


void uvloop::SinglePoolStrategy::setAlgo(const Algorithm &algo)
{
    m_client->setAlgo(algo);
}


void uvloop::SinglePoolStrategy::setProxy(const ProxyUrl &proxy)
{
    m_client->setProxy(proxy);
}


void uvloop::SinglePoolStrategy::stop()
{
    m_client->disconnect();
}


void uvloop::SinglePoolStrategy::tick(uint64_t now)
{
    m_client->tick(now);
}


void uvloop::SinglePoolStrategy::onClose(IClient *, int)
{
    if (!isActive()) {
        return;
    }

    m_active = false;
    m_listener->onPause(this);
}


void uvloop::SinglePoolStrategy::onJobReceived(IClient *client, const Job &job, const rapidjson::Value &params)
{
    m_listener->onJob(this, client, job, params);
}


void uvloop::SinglePoolStrategy::onLogin(IClient *client, rapidjson::Document &doc, rapidjson::Value &params)
{
    m_listener->onLogin(this, client, doc, params);
}


void uvloop::SinglePoolStrategy::onLoginSuccess(IClient *client)
{
    m_active = true;
    m_listener->onActive(this, client);
}


void uvloop::SinglePoolStrategy::onResultAccepted(IClient *client, const SubmitResult &result, const char *error)
{
    m_listener->onResultAccepted(this, client, result, error);
}


void uvloop::SinglePoolStrategy::onVerifyAlgorithm(const IClient *client, const Algorithm &algorithm, bool *ok)
{
    m_listener->onVerifyAlgorithm(this, client, algorithm, ok);
}
