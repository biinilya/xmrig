/* XMRig
 * Copyright (c) 2018-2021 SChernykh   <https://github.com/SChernykh>
 * Copyright (c) 2016-2021 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
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

#include "base/io/json/Json.h"
#include "3rdparty/rapidjson/document.h"


#include <cassert>
#include <cmath>
#include <istream>


namespace uvloop {

static const rapidjson::Value kNullValue;

} // namespace uvloop


bool uvloop::Json::getBool(const rapidjson::Value &obj, const char *key, bool defaultValue)
{
    if (isEmpty(obj)) {
        return defaultValue;
    }

    auto i = obj.FindMember(key);
    if (i != obj.MemberEnd() && i->value.IsBool()) {
        return i->value.GetBool();
    }

    return defaultValue;
}


bool uvloop::Json::isEmpty(const rapidjson::Value &obj)
{
    return !obj.IsObject() || obj.ObjectEmpty();
}


const char *uvloop::Json::getString(const rapidjson::Value &obj, const char *key, const char *defaultValue)
{
    if (isEmpty(obj)) {
        return defaultValue;
    }

    auto i = obj.FindMember(key);
    if (i != obj.MemberEnd() && i->value.IsString()) {
        return i->value.GetString();
    }

    return defaultValue;
}


const rapidjson::Value &uvloop::Json::getArray(const rapidjson::Value &obj, const char *key)
{
    if (isEmpty(obj)) {
        return kNullValue;
    }

    auto i = obj.FindMember(key);
    if (i != obj.MemberEnd() && i->value.IsArray()) {
        return i->value;
    }

    return kNullValue;
}


const rapidjson::Value &uvloop::Json::getObject(const rapidjson::Value &obj, const char *key)
{
    if (isEmpty(obj)) {
        return kNullValue;
    }

    auto i = obj.FindMember(key);
    if (i != obj.MemberEnd() && i->value.IsObject()) {
        return i->value;
    }

    return kNullValue;
}


const rapidjson::Value &uvloop::Json::getValue(const rapidjson::Value &obj, const char *key)
{
    if (isEmpty(obj)) {
        return kNullValue;
    }

    auto i = obj.FindMember(key);
    if (i != obj.MemberEnd()) {
        return i->value;
    }

    return kNullValue;
}


double uvloop::Json::getDouble(const rapidjson::Value &obj, const char *key, double defaultValue)
{
    if (isEmpty(obj)) {
        return defaultValue;
    }

    auto i = obj.FindMember(key);
    if (i != obj.MemberEnd() && (i->value.IsDouble() || i->value.IsLosslessDouble())) {
        return i->value.GetDouble();
    }

    return defaultValue;
}


int uvloop::Json::getInt(const rapidjson::Value &obj, const char *key, int defaultValue)
{
    if (isEmpty(obj)) {
        return defaultValue;
    }

    auto i = obj.FindMember(key);
    if (i != obj.MemberEnd() && i->value.IsInt()) {
        return i->value.GetInt();
    }

    return defaultValue;
}


int64_t uvloop::Json::getInt64(const rapidjson::Value &obj, const char *key, int64_t defaultValue)
{
    if (isEmpty(obj)) {
        return defaultValue;
    }

    auto i = obj.FindMember(key);
    if (i != obj.MemberEnd() && i->value.IsInt64()) {
        return i->value.GetInt64();
    }

    return defaultValue;
}


uvloop::String uvloop::Json::getString(const rapidjson::Value &obj, const char *key, size_t maxSize)
{
    if (isEmpty(obj)) {
        return {};
    }

    auto i = obj.FindMember(key);
    if (i == obj.MemberEnd() || !i->value.IsString()) {
        return {};
    }

    if (maxSize == 0 || i->value.GetStringLength() <= maxSize) {
        return i->value.GetString();
    }

    return { i->value.GetString(), maxSize };
}


uint64_t uvloop::Json::getUint64(const rapidjson::Value &obj, const char *key, uint64_t defaultValue)
{
    if (isEmpty(obj)) {
        return defaultValue;
    }

    auto i = obj.FindMember(key);
    if (i != obj.MemberEnd() && i->value.IsUint64()) {
        return i->value.GetUint64();
    }

    return defaultValue;
}


unsigned uvloop::Json::getUint(const rapidjson::Value &obj, const char *key, unsigned defaultValue)
{
    if (isEmpty(obj)) {
        return defaultValue;
    }

    auto i = obj.FindMember(key);
    if (i != obj.MemberEnd() && i->value.IsUint()) {
        return i->value.GetUint();
    }

    return defaultValue;
}


rapidjson::Value uvloop::Json::normalize(double value, bool zero)
{
    using namespace rapidjson;

    if (!std::isnormal(value)) {
        return zero ? Value(0.0) : Value(kNullType);
    }

    return Value(floor(value * 100.0) / 100.0);
}


bool uvloop::Json::convertOffset(std::istream &ifs, size_t offset, size_t &line, size_t &pos, std::vector<std::string> &s)
{
    std::string prev_t;
    std::string t;
    line = 0;
    pos = 0;
    size_t k = 0;

    while (!ifs.eof()) {
        prev_t = t;
        std::getline(ifs, t);
        k += t.length() + 1;
        ++line;

        if (k > offset) {
            pos = offset + t.length() + 1 - k + 1;

            s.clear();
            if (!prev_t.empty()) {
                s.emplace_back(prev_t);
            }
            s.emplace_back(t);

            return true;
        }
    }

    return false;
}


uvloop::JsonReader::JsonReader() :
    m_obj(kNullValue)
{}


bool uvloop::JsonReader::isEmpty() const
{
    return Json::isEmpty(m_obj);
}
