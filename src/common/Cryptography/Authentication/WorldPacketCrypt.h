/*
 * Copyright 2023 AzgathCore
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _WORLDPACKETCRYPT_H
#define _WORLDPACKETCRYPT_H

#include "AES.h"

class TC_COMMON_API WorldPacketCrypt
{
public:
    WorldPacketCrypt();

    void Init(Azgath::Crypto::AES::Key const& key);
    bool PeekDecryptRecv(uint8* data, size_t length);
    bool DecryptRecv(uint8* data, size_t length, Azgath::Crypto::AES::Tag& tag);
    bool EncryptSend(uint8* data, size_t length, Azgath::Crypto::AES::Tag& tag);

    bool IsInitialized() const { return _initialized; }

protected:
    Azgath::Crypto::AES _clientDecrypt;
    Azgath::Crypto::AES _serverEncrypt;
    uint64 _clientCounter;
    uint64 _serverCounter;
    bool _initialized;
};

#endif // _WORLDPACKETCRYPT_H
