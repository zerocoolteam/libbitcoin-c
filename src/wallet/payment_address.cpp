/**
 * Copyright (c) 2011-2016 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/bitcoin/c/wallet/payment_address.h>
#include <bitcoin/bitcoin/c/internal/wallet/payment_address.hpp>

#include <bitcoin/bitcoin/c/internal/chain/script.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/wallet/ec_private.hpp>
#include <bitcoin/bitcoin/c/internal/wallet/ec_public.hpp>

extern "C" {

BC_IMPLEMENT_BYTE_ARRAY__CUSTOM_NAMESPACE(payment, libbitcoin::wallet);

uint8_t bc_payment_address__mainnet_p2kh()
{
    return libbitcoin::wallet::payment_address::mainnet_p2kh;
}
uint8_t bc_payment_address__mainnet_p2sh()
{
    return libbitcoin::wallet::payment_address::mainnet_p2sh;
}
uint8_t bc_payment_address__testnet_p2kh()
{
    return libbitcoin::wallet::payment_address::testnet_p2kh;
}
uint8_t bc_payment_address__testnet_p2sh()
{
    return libbitcoin::wallet::payment_address::testnet_p2sh;
}

bc_payment_address_t* bc_payment_address__extract(
    const bc_script_t* script)
{
    const auto& address = libbitcoin::wallet::payment_address::extract(
        *script->obj);
    return new bc_payment_address_t{ new libbitcoin::wallet::payment_address(
        address) };
}
bc_payment_address_t* bc_payment_address__extract_Version(
    const bc_script_t* script, uint8_t p2kh_version)
{
    const auto& address = libbitcoin::wallet::payment_address::extract(
        *script->obj, p2kh_version);
    return new bc_payment_address_t{ new libbitcoin::wallet::payment_address(
        address) };
}
bc_payment_address_t* bc_payment_address__extract_Options(
    const bc_script_t* script, uint8_t p2kh_version, uint8_t p2sh_version)
{
    const auto& address = libbitcoin::wallet::payment_address::extract(
        *script->obj, p2kh_version, p2sh_version);
    return new bc_payment_address_t{ new libbitcoin::wallet::payment_address(
        address) };
}

bc_payment_address_t* bc_create_payment_address()
{
    return new bc_payment_address_t{ new libbitcoin::wallet::payment_address };
}
bc_payment_address_t* bc_create_payment_address_Payment(
    const bc_payment_t* decoded)
{
    return new bc_payment_address_t{ new libbitcoin::wallet::payment_address(
        *decoded->obj) };
}
bc_payment_address_t* bc_create_payment_address_Secret(
    const bc_ec_private_t* secret)
{
    return new bc_payment_address_t{ new libbitcoin::wallet::payment_address(
        *secret->obj) };
}
bc_payment_address_t* bc_create_payment_address_String(
    const char* address)
{
    return new bc_payment_address_t{ new libbitcoin::wallet::payment_address(
        address) };
}
bc_payment_address_t* bc_create_payment_address_copy(
    const bc_payment_address_t* other)
{
    return new bc_payment_address_t{ new libbitcoin::wallet::payment_address(
        *other->obj) };
}
bc_payment_address_t* bc_create_payment_address_Hash(
    const bc_short_hash_t* hash)
{
    return new bc_payment_address_t{ new libbitcoin::wallet::payment_address(
        *hash->obj) };
}
bc_payment_address_t* bc_create_payment_address_Hash_Version(
    const bc_short_hash_t* hash, uint8_t version)
{
    return new bc_payment_address_t{ new libbitcoin::wallet::payment_address(
        *hash->obj, version) };
}
bc_payment_address_t* bc_create_payment_address_Point(
    const bc_ec_public_t* point)
{
    return new bc_payment_address_t{ new libbitcoin::wallet::payment_address(
        *point->obj) };
}
bc_payment_address_t* bc_create_payment_address_Point_Version(
    const bc_ec_public_t* point, uint8_t version)
{
    return new bc_payment_address_t{ new libbitcoin::wallet::payment_address(
        *point->obj, version) };
}
bc_payment_address_t* bc_create_payment_address_Script(
    const bc_script_t* script)
{
    return new bc_payment_address_t{ new libbitcoin::wallet::payment_address(
        *script->obj) };
}
bc_payment_address_t* bc_create_payment_address_Script_Version(
    const bc_script_t* script, uint8_t version)
{
    return new bc_payment_address_t{ new libbitcoin::wallet::payment_address(
        *script->obj, version) };
}
void bc_destroy_payment_address(bc_payment_address_t* self)
{
    delete self->obj;
    delete self;
}

/// Operators.
bool bc_payment_address__less_than(
    const bc_payment_address_t* self, const bc_payment_address_t* other)
{
    return *self->obj < *other->obj;
}
bool bc_payment_address__equals(
    const bc_payment_address_t* self, const bc_payment_address_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_payment_address__not_equals(
    const bc_payment_address_t* self, const bc_payment_address_t* other)
{
    return *self->obj != *other->obj;
}
bc_payment_address_t* bc_payment_address__copy(
    bc_payment_address_t* self, const bc_payment_address_t* other)
{
    *self->obj = *other->obj;
    return self;
}
// stream operators ignored.

/// Cast operators.
bool bc_payment_address__is_valid(const bc_payment_address_t* self)
{
    return static_cast<bool>(*self->obj);
}

/// Serializer.
bc_string_t* bc_payment_address__encoded(const bc_payment_address_t* self)
{
    return bc_create_string_StdString(self->obj->encoded());
}

/// Accessors.
uint8_t bc_payment_address__version(const bc_payment_address_t* self)
{
    return self->obj->version();
}
bc_short_hash_t* bc_payment_address__hash(const bc_payment_address_t* self)
{
    return new bc_short_hash_t{ new libbitcoin::short_hash(
        self->obj->hash()) };
}

/// Methods.
bc_payment_t* bc_payment_address__payment(const bc_payment_address_t* self)
{
    return new bc_payment_t{ new libbitcoin::wallet::payment(
        self->obj->to_payment()) };
}

}

