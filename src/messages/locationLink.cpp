// A C++17 library for language servers.
// Copyright © 2019 otreblan
//
// libclsp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libclsp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libclsp.  If not, see <http://www.gnu.org/licenses/>.

#include <libclsp/messages/locationLink.hpp>

namespace libclsp
{

const String LocationLink::originSelectionRangeKey = "originSelectionRange";
const String LocationLink::targetUriKey            = "targetUri";
const String LocationLink::targetRangeKey          = "targetRange";
const String LocationLink::targetSelectionRangeKey = "targetSelectionRange";

LocationLink::LocationLink(optional<Range> originSelectionRange,
	DocumentUri targetUri,
	Range targetRange,
	Range targetSelectionRange):
		originSelectionRange(originSelectionRange),
		targetUri(targetUri),
		targetRange(targetRange),
		targetSelectionRange(targetSelectionRange){};

LocationLink::~LocationLink(){};

}