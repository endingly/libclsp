// A C++17 library for language servers.
// Copyright © 2019-2020 otreblan
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

#include <libclsp/types/completion.hpp>

namespace clsp
{

using namespace std;

const String CompletionOptions::triggerCharactersKey   = "triggerCharacters";
const String CompletionOptions::allCommitCharactersKey = "allCommitCharacters";
const String CompletionOptions::resolveProviderKey     = "resolveProvider";

CompletionOptions::CompletionOptions(optional<ProgressToken> workDoneProgress,
	optional<vector<String>> triggerCharacters,
	optional<vector<String>> allCommitCharacters,
	optional<Boolean> resolveProvider):
		WorkDoneProgressOptions(workDoneProgress),
		triggerCharacters(triggerCharacters),
		allCommitCharacters(allCommitCharacters),
		resolveProvider(resolveProvider)
{};

CompletionOptions::CompletionOptions(){};
CompletionOptions::~CompletionOptions(){};


CompletionRegistrationOptions::
	CompletionRegistrationOptions(
		variant<DocumentSelector, Null> documentSelector,
		optional<ProgressToken> workDoneProgress,
		optional<vector<String>> triggerCharacters,
		optional<vector<String>> allCommitCharacters,
		optional<Boolean> resolveProvider):
			TextDocumentRegistrationOptions(documentSelector),
			CompletionOptions(workDoneProgress,
				triggerCharacters,
				allCommitCharacters,
				resolveProvider)
{};

CompletionRegistrationOptions::CompletionRegistrationOptions(){};
CompletionRegistrationOptions::~CompletionRegistrationOptions(){};


const String CompletionContext::triggerKindKey      = "triggerKind";
const String CompletionContext::triggerCharacterKey = "triggerCharacter";

CompletionContext::CompletionContext(CompletionTriggerKind triggerKind,
	optional<String> triggerCharacter):
		triggerKind(triggerKind),
		triggerCharacter(triggerCharacter)
{};

CompletionContext::CompletionContext(){};
CompletionContext::~CompletionContext(){};

void CompletionContext::fillInitializer(ObjectInitializer& initializer)
{
	auto& setterMap = initializer.setterMap;
	auto& neededMap = initializer.neededMap;

	// Value setters

	// triggerKind:
	setterMap.emplace(
		triggerKindKey,
		ValueSetter{
			// String
			{},

			// Number
			[this, &neededMap](Number n)
			{
				if(holds_alternative<int>(n))
				{
					int i = get<int>(n);

					triggerKind = (CompletionTriggerKind)i;

					neededMap[triggerKindKey] = true;
				}
				else
				{
					// TODO
					// Exception or something
				}
			},

			// Boolean
			{},

			// Null
			{},

			// Array
			{},

			// Object
			{}
		}
	);

	// triggerCharacter?:
	setterMap.emplace(
		triggerCharacterKey,
		ValueSetter{
			// String
			[this](String str)
			{
				triggerCharacter = str;
			},

			// Number
			{},

			// Boolean
			{},

			// Null
			{},

			// Array
			{},

			// Object
			{}
		}
	);

	// Needed members
	neededMap.emplace(triggerKindKey, 0);

	// This
	initializer.object = this;
}

const String CompletionParams::contextKey = "context";

CompletionParams::CompletionParams(TextDocumentIdentifier textDocument,
	Position position,
	optional<ProgressToken> workDoneToken,
	optional<ProgressToken> partialResultToken,
	optional<CompletionContext> context):
		TextDocumentPositionParams(textDocument, position),
		WorkDoneProgressParams(workDoneToken),
		PartialResultParams(partialResultToken),
		context(context)
{};

CompletionParams::CompletionParams(){};
CompletionParams::~CompletionParams(){};


void CompletionParams::fillInitializer(ObjectInitializer& initializer)
{
	auto* handler = initializer.handler;

	auto& setterMap = initializer.setterMap;

	// Parents
	TextDocumentPositionParams::fillInitializer(initializer);
	WorkDoneProgressParams::fillInitializer(initializer);
	PartialResultParams::fillInitializer(initializer);

	// Value setters

	// context?:
	setterMap.emplace(
		contextKey,
		ValueSetter{
			// String
			{},

			// Number
			{},

			// Boolean
			{},

			// Null
			{},

			// Array
			{},

			// Object
			[this, handler]()
			{
				context.emplace();

				handler->pushInitializer();
				context->fillInitializer(handler->objectStack.top());
			}
		}
	);

	// This
	initializer.object = this;
}

const String CompletionItem::labelKey               = "label";
const String CompletionItem::kindKey                = "kind";
const String CompletionItem::tagsKey                = "tags";
const String CompletionItem::detailKey              = "detail";
const String CompletionItem::documentationKey       = "documentation";
const String CompletionItem::deprecatedKey          = "deprecated";
const String CompletionItem::preselectKey           = "preselect";
const String CompletionItem::sortTextKey            = "sortText";
const String CompletionItem::filterTextKey          = "filterText";
const String CompletionItem::insertTextKey          = "insertText";
const String CompletionItem::insertTextFormatKey    = "insertTextFormat";
const String CompletionItem::textEditKey            = "textEdit";
const String CompletionItem::additionalTextEditsKey = "additionalTextEdits";
const String CompletionItem::commitCharactersKey    = "commitCharacters";
const String CompletionItem::commandKey             = "command";
const String CompletionItem::dataKey                = "data";

CompletionItem::CompletionItem(String label,
	optional<CompletionItemKind> kind,
	optional<vector<CompletionItemTag>> tags,
	optional<String> detail,
	optional<variant<String,MarkupContent>> documentation,
	optional<Boolean> deprecated,
	optional<Boolean> preselect,
	optional<String> sortText,
	optional<String> filterText,
	optional<String> insertText,
	optional<InsertTextFormat> insertTextFormat,
	optional<TextEdit> textEdit,
	optional<vector<TextEdit>> additionalTextEdits,
	optional<vector<String>> commitCharacters,
	optional<Command> command,
	optional<Any> data):
		label(label),
		kind(kind),
		tags(tags),
		detail(detail),
		documentation(documentation),
		deprecated(deprecated),
		preselect(preselect),
		sortText(sortText),
		filterText(filterText),
		insertText(insertText),
		insertTextFormat(insertTextFormat),
		textEdit(textEdit),
		additionalTextEdits(additionalTextEdits),
		commitCharacters(commitCharacters),
		command(command),
		data(data)
{};

CompletionItem::CompletionItem(){};
CompletionItem::~CompletionItem(){};


const String CompletionList::isIncompleteKey = "isIncomplete";
const String CompletionList::itemsKey        = "items";

CompletionList::CompletionList(Boolean isIncomplete,
	vector<CompletionItem> items):
		isIncomplete(isIncomplete),
		items(items)
{};

CompletionList::CompletionList(){};
CompletionList::~CompletionList(){};


const String CompletionClientCapabilities::
	dynamicRegistrationKey = "dynamicRegistration";

const String CompletionClientCapabilities::
	completionItemKey      = "completionItem";

const String CompletionClientCapabilities::
	completionItemKindKey  = "completionItemKind";

const String CompletionClientCapabilities::
	contextSupportKey      = "contextSupport";

CompletionClientCapabilities::
	CompletionClientCapabilities(optional<Boolean> dynamicRegistration,
		optional<CompletionItem> completionItem,
		optional<CompletionItemKind> completionItemKind,
		optional<Boolean> contextSupport):
			dynamicRegistration(dynamicRegistration),
			completionItem(completionItem),
			completionItemKind(completionItemKind),
			contextSupport(contextSupport)
{};

CompletionClientCapabilities::CompletionClientCapabilities(){};
CompletionClientCapabilities::~CompletionClientCapabilities(){};

void CompletionClientCapabilities::fillInitializer(ObjectInitializer& initializer)
{
	auto* handler = initializer.handler;

	auto& setterMap = initializer.setterMap;

	// Value setters

	// dynamicRegistration?:
	setterMap.emplace(
		dynamicRegistrationKey,
		ValueSetter{
			// String
			{},

			// Number
			{},

			// Boolean
			[this](Boolean b)
			{
				dynamicRegistration = b;
			},

			// Null
			{},

			// Array
			{},

			// Object
			{}
		}
	);

	// completionItem?:
	setterMap.emplace(
		completionItemKey,
		ValueSetter{
			// String
			{},

			// Number
			{},

			// Boolean
			{},

			// Null
			{},

			// Array
			{},

			// Object
			[this, handler]()
			{
				completionItem.emplace();

				handler->pushInitializer();
				completionItem->fillInitializer(handler->objectStack.top());
			}
		}
	);

	// completionItemKind?:
	setterMap.emplace(
		completionItemKindKey,
		ValueSetter{
			// String
			{},

			// Number
			{},

			// Boolean
			{},

			// Null
			{},

			// Array
			{},

			// Object
			[this, handler]()
			{
				completionItemKind.emplace();

				handler->pushInitializer();
				completionItemKind->fillInitializer(handler->objectStack.top());
			}
		}
	);

	// contextSupport?:
	setterMap.emplace(
		contextSupportKey,
		ValueSetter{
			// String
			{},

			// Number
			{},

			// Boolean
			[this](Boolean b)
			{
				contextSupport = b;
			},

			// Null
			{},

			// Array
			{},

			// Object
			{}
		}
	);

	// This
	initializer.object = this;
}


const String CompletionClientCapabilities::CompletionItem::
	snippetSupportKey          = "snippetSupport";

const String CompletionClientCapabilities::CompletionItem::
	commitCharactersSupportKey = "commitCharactersSupport";

const String CompletionClientCapabilities::CompletionItem::
	documentationFormatKey     = "documentationFormat";

const String CompletionClientCapabilities::CompletionItem::
	deprecatedSupportKey       = "deprecatedSupport";

const String CompletionClientCapabilities::CompletionItem::
	preselectSupportKey        = "preselectSupport";

const String CompletionClientCapabilities::CompletionItem::
	tagSupportKey              = "tagSupport";

CompletionClientCapabilities::CompletionItem::
	CompletionItem(optional<Boolean> snippetSupport,
		optional<Boolean> commitCharactersSupport,
		optional<vector<MarkupKind>> documentationFormat,
		optional<Boolean> deprecatedSupport,
		optional<Boolean> preselectSupport,
		optional<TagSupport> tagSupport):
			snippetSupport(snippetSupport),
			commitCharactersSupport(commitCharactersSupport),
			documentationFormat(documentationFormat),
			deprecatedSupport(deprecatedSupport),
			preselectSupport(preselectSupport),
			tagSupport(tagSupport)
{};

CompletionClientCapabilities::CompletionItem::CompletionItem(){};
CompletionClientCapabilities::CompletionItem::~CompletionItem(){};


void CompletionClientCapabilities::CompletionItem::
	fillInitializer(ObjectInitializer& initializer)
{
	auto* handler = initializer.handler;

	auto& setterMap = initializer.setterMap;

	// Value setters

	// snippetSupport?:
	setterMap.emplace(
		snippetSupportKey,
		ValueSetter{
			// String
			{},

			// Number
			{},

			// Boolean
			[this](Boolean b)
			{
				snippetSupport = b;
			},

			// Null
			{},

			// Array
			{},

			// Object
			{}
		}
	);

	// commitCharactersSupport?:
	setterMap.emplace(
		commitCharactersSupportKey,
		ValueSetter{
			// String
			{},

			// Number
			{},

			// Boolean
			[this](Boolean b)
			{
				commitCharactersSupport = b;
			},

			// Null
			{},

			// Array
			{},

			// Object
			{}
		}
	);

	// documentationFormat?:
	setterMap.emplace(
		documentationFormatKey,
		ValueSetter{
			// String
			{},

			// Number
			{},

			// Boolean
			{},

			// Null
			{},

			// Array
			[this, handler]()
			{
				documentationFormat.emplace();

				handler->pushInitializer();

				auto* maker = new DocumentationFormatMaker(documentationFormat.value());

				maker->fillInitializer(handler->objectStack.top());
			},

			// Object
			{}
		}
	);

	// deprecatedSupport?:
	setterMap.emplace(
		deprecatedSupportKey,
		ValueSetter{
			// String
			{},

			// Number
			{},

			// Boolean
			[this](Boolean b)
			{
				deprecatedSupport = b;
			},

			// Null
			{},

			// Array
			{},

			// Object
			{}
		}
	);

	// preselectSupport?:
	setterMap.emplace(
		preselectSupportKey,
		ValueSetter{
			// String
			{},

			// Number
			{},

			// Boolean
			[this](Boolean b)
			{
				preselectSupport = b;
			},

			// Null
			{},

			// Array
			{},

			// Object
			{}
		}
	);

	// tagSupport?:
	setterMap.emplace(
		tagSupportKey,
		ValueSetter{
			// String
			{},

			// Number
			{},

			// Boolean
			{},

			// Null
			{},

			// Array
			{},

			// Object
			[this, handler]()
			{
				tagSupport.emplace();

				handler->pushInitializer();
				tagSupport->fillInitializer(handler->objectStack.top());
			}
		}
	);

	// This
	initializer.object = this;
}


CompletionClientCapabilities::CompletionItem::DocumentationFormatMaker::
	DocumentationFormatMaker(vector<MarkupKind> &parentArray):
		parentArray(parentArray)
{};

CompletionClientCapabilities::CompletionItem::DocumentationFormatMaker::
	~DocumentationFormatMaker()
{};

void CompletionClientCapabilities::CompletionItem::DocumentationFormatMaker::
	fillInitializer(ObjectInitializer& initializer)
{
	// ObjectMaker
	initializer.objectMaker = unique_ptr<ObjectT>(this);

	auto& extraSetter = initializer.extraSetter;

	// Value setters

	// MarkupKind[]
	extraSetter =
	{
		// String
		[this](String str)
		{
			parentArray.emplace_back(str);
		},

		// Number
		{},

		// Boolean
		{},

		// Null
		{},

		// Array
		{},

		// Object
		{}
	};

	// This
	initializer.object = this;
}


const string CompletionClientCapabilities::CompletionItem::TagSupport::
	valueSetKey = "valueSet";

CompletionClientCapabilities::CompletionItem::TagSupport::
	TagSupport(vector<CompletionItemTag> valueSet):
		valueSet(valueSet)
{};

CompletionClientCapabilities::CompletionItem::TagSupport::TagSupport(){};
CompletionClientCapabilities::CompletionItem::TagSupport::~TagSupport(){};

void CompletionClientCapabilities::CompletionItem::TagSupport::
	fillInitializer(ObjectInitializer& initializer)
{
	auto* handler = initializer.handler;

	auto& setterMap = initializer.setterMap;
	auto& neededMap = initializer.neededMap;

	// Value setters

	// valueSet:
	setterMap.emplace(
		valueSetKey,
		ValueSetter{
			// String
			{},

			// Number
			{},

			// Boolean
			{},

			// Null
			{},

			// Array
			[this, handler, &neededMap]()
			{
				handler->pushInitializer();

				auto* maker = new ValueSetMaker(valueSet);

				maker->fillInitializer(handler->objectStack.top());

				neededMap[valueSetKey] = true;
			},

			// Object
			{}
		}
	);


	// This
	initializer.object = this;
}


CompletionClientCapabilities::CompletionItem::TagSupport::ValueSetMaker::
	ValueSetMaker(vector<CompletionItemTag> &parentArray):
		parentArray(parentArray)
{};

CompletionClientCapabilities::CompletionItem::TagSupport::ValueSetMaker::
	~ValueSetMaker()
{};

void CompletionClientCapabilities::CompletionItem::TagSupport::ValueSetMaker::
	fillInitializer(ObjectInitializer& initializer)
{
	// ObjectMaker
	initializer.objectMaker = unique_ptr<ObjectT>(this);

	auto& extraSetter = initializer.extraSetter;

	// Value setters

	// CompletionItemTag[]
	extraSetter =
	{
		// String
		{},

		// Number
		[this](Number n)
		{
			if(holds_alternative<int>(n))
			{
				int i = get<int>(n);

				parentArray.emplace_back((CompletionItemTag)i);
			}
			else
			{
				// TODO
				// An exception or something
			}
		},

		// Boolean
		{},

		// Null
		{},

		// Array
		{},

		// Object
		{}
	};

	// This
	initializer.object = this;
}

const String CompletionClientCapabilities::CompletionItemKind::
	valueSetKey = "valueSet";

CompletionClientCapabilities::CompletionItemKind::
	CompletionItemKind(optional<vector<clsp::CompletionItemKind>> valueSet):
		valueSet(valueSet)
{};

CompletionClientCapabilities::CompletionItemKind::CompletionItemKind(){};
CompletionClientCapabilities::CompletionItemKind::~CompletionItemKind(){};

void CompletionClientCapabilities::CompletionItemKind::
	fillInitializer(ObjectInitializer& initializer)
{
	auto* handler = initializer.handler;

	auto& setterMap = initializer.setterMap;

	// Value setters

	// valueSet:
	setterMap.emplace(
		valueSetKey,
		ValueSetter{
			// String
			{},

			// Number
			{},

			// Boolean
			{},

			// Null
			{},

			// Array
			[this, handler]()
			{
				valueSet.emplace();

				handler->pushInitializer();

				auto* maker = new ValueSetMaker(valueSet.value());

				maker->fillInitializer(handler->objectStack.top());
			},

			// Object
			{}
		}
	);


	// This
	initializer.object = this;
}

CompletionClientCapabilities::CompletionItemKind::ValueSetMaker::
	ValueSetMaker(vector<clsp::CompletionItemKind> &parentArray):
		parentArray(parentArray)
{};

CompletionClientCapabilities::CompletionItemKind::ValueSetMaker::
	~ValueSetMaker()
{};

void CompletionClientCapabilities::CompletionItemKind::ValueSetMaker::
	fillInitializer(ObjectInitializer& initializer)
{
	// ObjectMaker
	initializer.objectMaker = unique_ptr<ObjectT>(this);

	auto& extraSetter = initializer.extraSetter;

	// Value setters

	// CompletionItemKind[]
	extraSetter =
	{
		// String
		{},

		// Number
		[this](Number n)
		{
			if(holds_alternative<int>(n))
			{
				int i = get<int>(n);

				parentArray.emplace_back((clsp::CompletionItemKind)i);
			}
			else
			{
				// TODO
				// An exception or something
			}
		},

		// Boolean
		{},

		// Null
		{},

		// Array
		{},

		// Object
		{}
	};

	// This
	initializer.object = this;
}

}
