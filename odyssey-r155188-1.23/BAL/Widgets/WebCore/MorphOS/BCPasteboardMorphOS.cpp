/*
 * Copyright (C) 2009-2013 Fabien Coeurjoly.
 * Copyright (C) 2008 Pleyo.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Pleyo nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY PLEYO AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PLEYO OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "Logging.h"
#include "Clipboard.h"
#include "Pasteboard.h"

#include "CachedImage.h"
#include "DataObject.h"
#include "DocumentFragment.h"
#include "Editor.h"
#include "Frame.h"
#include "HTMLImageElement.h"
#include "HTMLInputElement.h"
#include "HTMLNames.h"
#include "HTMLParserIdioms.h"
#include "Image.h"
#include "KURL.h"
#include "PasteboardHelper.h"
#include "RenderImage.h"
#include "markup.h"

#if ENABLE(SVG)
#include "SVGNames.h"
#include "XLinkNames.h"
#endif

#include <cstdio>

#include <devices/clipboard.h>
#include <libraries/locale.h>
#include <proto/exec.h>    
#include <proto/iffparse.h>
#include <proto/intuition.h>
#include <proto/datatypes.h>
#include <proto/iffparse.h>
#include <datatypes/textclass.h>
#include <datatypes/pictureclass.h>
#include "../../../../WebKit/OrigynWebBrowser/Api/MorphOS/utils.h"
#include "../../../../WebKit/OrigynWebBrowser/Api/MorphOS/clipboard.h"

#undef String

/* Debug output to serial handled via D(bug("....."));
*  See Base/debug.h for details.
*  D(x)    - to disable debug
*  D(x) x  - to enable debug
*/
#define D(x)

namespace WebCore {

static void writeUTF8(const char* data, size_t len)
{
    IFFHandle *ih;

    bool copied = false;

	if(data && len)
	{
		char *converted = utf8_to_local(data);

		if(converted)
		{
			if ((ih = AllocIFF()))
			{
				if (ClipboardHandle *ch = OpenClipboard(PRIMARY_CLIP))
				{
					ih->iff_Stream = (uint32)ch;
					InitIFFasClip(ih);

					if (0 == OpenIFF(ih, IFFF_WRITE))
					{
						if (0 == PushChunk(ih, ID_FTXT, ID_FORM, IFFSIZE_UNKNOWN))
						{
							if (0 == PushChunk(ih, 0, ID_CHRS, IFFSIZE_UNKNOWN)
							 && WriteChunkBytes(ih, (APTR)converted, strlen(converted)) > 0
							 && 0 == PopChunk(ih)
							 && 0 == PushChunk(ih, 0, ID_UTF8, IFFSIZE_UNKNOWN))
							{
								if (WriteChunkBytes(ih, (APTR)data, len) > 0)
									copied = true;
								PopChunk(ih);
							}

							PopChunk(ih);
						}
						CloseIFF(ih);
					}
					CloseClipboard(ch);
				}
				FreeIFF(ih);
			}
			free(converted);
		}
	}

    if (!copied)
	{
        DisplayBeep(NULL);
	}
}

enum ClipboardDataType {
    ClipboardDataTypeText,
    ClipboardDataTypeMarkup,
    ClipboardDataTypeURIList,
    ClipboardDataTypeURL,
    ClipboardDataTypeImage,
    ClipboardDataTypeUnknown
};

PassOwnPtr<Pasteboard> Pasteboard::create(int clipboard)
{
	D(bug("Pasteboard::create(clipboard=%d)\n", clipboard));
	return adoptPtr(new Pasteboard(clipboard));
}

PassOwnPtr<Pasteboard> Pasteboard::create(PassRefPtr<DataObjectMorphOS> dataObject, int clipboard)
{
	D(bug("Pasteboard::create(dataobject %p clipboard %d)\n", dataObject.get(), clipboard));
    return adoptPtr(new Pasteboard(dataObject, clipboard));
}

PassOwnPtr<Pasteboard> Pasteboard::createForCopyAndPaste()
{
	D(bug("Pasteboard::createForCopyAndPaste\n"));
	return create(0);
}

PassOwnPtr<Pasteboard> Pasteboard::createForGlobalSelection()
{
	D(bug("Pasteboard::createForGlobalSelection\n"));
	return create(0);
}

PassOwnPtr<Pasteboard> Pasteboard::createPrivate()
{
	D(bug("Pasteboard::createPrivate\n"));
	return create(DataObjectMorphOS::create());
}

PassOwnPtr<Pasteboard> Pasteboard::createForDragAndDrop()
{
	D(bug("Pasteboard::createForDragAndDrop\n"));
	return create(DataObjectMorphOS::create(), 1);
}

PassOwnPtr<Pasteboard> Pasteboard::createForDragAndDrop(const DragData& dragData)
{
	D(bug("Pasteboard::createForDragAndDrop(dragData)\n"));
	return create(dragData.platformData(), 1);
}

Pasteboard::Pasteboard(PassRefPtr<DataObjectMorphOS> dataObject, int clipboard)
    : m_dataObject(dataObject)
	, m_morphosClipboard(clipboard)
{
	D(bug("Pasteboard::Pasteboard(dataObject %p, clipboard %d)\n", dataObject.get(), clipboard));
    ASSERT(m_dataObject);
}

Pasteboard::Pasteboard(int clipboard)
	: m_dataObject(DataObjectMorphOS::forClipboard(clipboard))
	, m_morphosClipboard(clipboard)
{
	D(bug("Pasteboard::Pasteboard(clipboard %d)\n", clipboard));
    ASSERT(m_dataObject);
}

Pasteboard::~Pasteboard()
{
}

PassRefPtr<DataObjectMorphOS> Pasteboard::dataObject() const
{
    return m_dataObject;
}

static ClipboardDataType dataObjectTypeFromHTMLClipboardType(const String& rawType)
{
    String type(rawType.stripWhiteSpace());

	D(bug("dataObjectTypeFromHTMLClipboardType %s\n", type.utf8().data()));

    // Two special cases for IE compatibility
    if (type == "Text" || type == "text")
        return ClipboardDataTypeText;
    if (type == "URL")
        return ClipboardDataTypeURL;

    // From the Mac port: Ignore any trailing charset - JS strings are
    // Unicode, which encapsulates the charset issue.
    if (type == "text/plain" || type.startsWith("text/plain;"))
        return ClipboardDataTypeText;
    if (type == "text/html" || type.startsWith("text/html;"))
        return ClipboardDataTypeMarkup;
    if (type == "Files" || type == "text/uri-list" || type.startsWith("text/uri-list;"))
        return ClipboardDataTypeURIList;

    // Not a known type, so just default to using the text portion.
    return ClipboardDataTypeUnknown;
}

bool Pasteboard::writeString(const String& type, const String& data)
{
	D(bug("Pasteboard::writeString %s %s\n", type.utf8().data(), data.utf8().data()));

    switch (dataObjectTypeFromHTMLClipboardType(type)) {
    case ClipboardDataTypeURIList:
    case ClipboardDataTypeURL:
	{
		if(m_morphosClipboard == 0)
		{
			/* Copy to system clipboard first (clipboard monitor will reset rich content as a result) */
			char *text = strdup(data.utf8().data());
			writeUTF8(text, strlen(text));
			free(text);
		}
        m_dataObject->setURIList(data);
        return true;
	}
    case ClipboardDataTypeMarkup:
        m_dataObject->setMarkup(data);
        return true;
    case ClipboardDataTypeText:
	{
		if(m_morphosClipboard == 0)
		{
			/* Copy to system clipboard first (clipboard monitor will reset rich content as a result) */
			char *text = strdup(data.utf8().data());
			writeUTF8(text, strlen(text));
			free(text);
		}
        m_dataObject->setText(data);
        return true;
	}
    case ClipboardDataTypeImage:
    case ClipboardDataTypeUnknown:
        break;
    }

    return false;
}

void Pasteboard::writeSelection(Range* selectedRange, bool canSmartCopyOrDelete, Frame* frame, ShouldSerializeSelectedTextForClipboard shouldSerializeSelectedTextForClipboard)
{
	String text = shouldSerializeSelectedTextForClipboard == IncludeImageAltTextForClipboard ? frame->editor().selectedTextForClipboard() : frame->editor().selectedText();

	D(bug("Pasteboard::writeSelection %s %d\n", text.utf8().data(), m_morphosClipboard));

	if(m_morphosClipboard == 0)
	{
	    /* Copy to system clipboard first (clipboard monitor will reset rich content as a result) */
		char *data = strdup(text.utf8().data());
	    writeUTF8(data, strlen(data));
		free(data);
	}

	/* Then store to internal clipboard */
    m_dataObject->clearAll();
	m_dataObject->setText(text);
    m_dataObject->setMarkup(createMarkup(selectedRange, 0, AnnotateForInterchange, false, ResolveNonLocalURLs));
}

void Pasteboard::writePlainText(const String& text, SmartReplaceOption smartReplaceOption)
{
	D(bug("Pasteboard::writePlainText %s %d\n", text.utf8().data(), m_morphosClipboard));

	if(m_morphosClipboard == 0)
	{
	    /* Copy to system clipboard first (clipboard monitor will reset rich content as a result) */
		char *data = strdup(text.utf8().data());
	    writeUTF8(data, strlen(data));
		free(data);
	}

	/* Then store to internal clipboard */
    m_dataObject->clearAll();
    m_dataObject->setText(text);
}

void Pasteboard::writeURL(const KURL& url, const String& label, Frame* frame)
{
	D(bug("Pasteboard::writeURL %s %d\n", url.string().utf8().data(), m_morphosClipboard));

    ASSERT(!url.isEmpty());

	if(m_morphosClipboard == 0)
	{
	    /* Copy to system clipboard first (clipboard monitor will reset rich content as a result) */
	    WTF::CString utf8 = url.string().utf8();
	    const char *data = utf8.data();
	    writeUTF8(data, strlen(data));
	}

	/* Then store to internal clipboard */
    m_dataObject->clearAll();
    m_dataObject->setURL(url, label);
}

static KURL getURLForImageNode(Node* node)
{
    // FIXME: Later this code should be shared with Chromium somehow. Chances are all platforms want it.
    AtomicString urlString;
    if (isHTMLImageElement(node) || isHTMLInputElement(node))
        urlString = toElement(node)->getAttribute(HTMLNames::srcAttr);
#if ENABLE(SVG)
    else if (node->hasTagName(SVGNames::imageTag))
        urlString = toElement(node)->getAttribute(XLinkNames::hrefAttr);
#endif
    else if (node->hasTagName(HTMLNames::embedTag) || node->hasTagName(HTMLNames::objectTag)) {
        Element* element = toElement(node);
        urlString = element->imageSourceURL();
    }
    return urlString.isEmpty() ? KURL() : node->document().completeURL(stripLeadingAndTrailingHTMLSpaces(urlString));
}

void Pasteboard::writeImage(Node* node, const KURL&, const String& title)
{
    ASSERT(node);

	D(bug("Pasteboard::writeImage\n"));

    if (!(node->renderer() && node->renderer()->isImage()))
        return;

    RenderImage* renderer = toRenderImage(node->renderer());
    CachedImage* cachedImage = renderer->cachedImage();
    if (!cachedImage || cachedImage->errorOccurred())
        return;
    Image* image = cachedImage->imageForRenderer(renderer);
    ASSERT(image);

	if(m_morphosClipboard == 0)
	{
		/* Copy to system clipboard */
	    bool copied = false;

	    if(image)
	    {
	        cairo_surface_t *surface = image->nativeImageForCurrentFrame().leakRef();
			if(surface)
			{
			    ChkImage img;

			    img.width = image->width();
			    img.height = image->height();
			    img.data.p = cairo_image_surface_get_data(surface);

			    if(copyImageToClipboard(&img))
			        copied = true;
			}
	    }

	    if (!copied)
	        DisplayBeep(NULL);
	}

	/* Copy to internal clipboard */

    m_dataObject->clearAll();

    KURL url = getURLForImageNode(node);
	D(bug("Pasteboard::writeImage url %s %d\n", url.string().utf8().data(), m_morphosClipboard));
    if (!url.isEmpty()) {
        m_dataObject->setURL(url, title);
        m_dataObject->setMarkup(createMarkup(toElement(node), IncludeNode, 0, ResolveAllURLs));
    }

	m_dataObject->setImage(image->nativeImageForCurrentFrame().get());
}

void Pasteboard::writePasteboard(const Pasteboard& sourcePasteboard)
{
	D(bug("Pasteboard::writePasteboard\n"));

	RefPtr<DataObjectMorphOS> sourceDataObject = sourcePasteboard.dataObject();
    m_dataObject->clearAll();

    if (sourceDataObject->hasText())
        m_dataObject->setText(sourceDataObject->text());
    if (sourceDataObject->hasMarkup())
        m_dataObject->setMarkup(sourceDataObject->markup());
    if (sourceDataObject->hasURL())
        m_dataObject->setURL(sourceDataObject->url(), sourceDataObject->urlLabel());
    if (sourceDataObject->hasURIList())
        m_dataObject->setURIList(sourceDataObject->uriList());
    if (sourceDataObject->hasImage())
        m_dataObject->setImage(sourceDataObject->image());

#warning "XXX: what to do here, exactly?"
	/*
    if (m_gtkClipboard)
        PasteboardHelper::defaultPasteboardHelper()->writeClipboardContents(m_gtkClipboard);
	*/
}

void Pasteboard::clear()
{
	D(bug("Pasteboard::clear\n"));

    // We do not clear filenames. According to the spec: "The clearData() method
    // does not affect whether any files were included in the drag, so the types
    // attribute's list might still not be empty after calling clearData() (it would
    // still contain the "Files" string if any files were included in the drag)."
    m_dataObject->clearAllExceptFilenames();

#warning "XXX: what to do here, exactly?"
}

void Pasteboard::clear(const String& type)
{
	D(bug("Pasteboard::clear(%s)\n", type.utf8().data()));

    switch (dataObjectTypeFromHTMLClipboardType(type)) {
    case ClipboardDataTypeURIList:
    case ClipboardDataTypeURL:
        m_dataObject->clearURIList();
        break;
    case ClipboardDataTypeMarkup:
        m_dataObject->clearMarkup();
        break;
    case ClipboardDataTypeText:
        m_dataObject->clearText();
        break;
    case ClipboardDataTypeImage:
        m_dataObject->clearImage();
        break;
    case ClipboardDataTypeUnknown:
        m_dataObject->clearAll();
        break;
    }

#warning "XXX: what to do here, exactly?"
}

bool Pasteboard::canSmartReplace()
{
	return false;
}

static void setWithClipboardContents(Pasteboard *pasteboard, int clipboard)
{
	String text = pasteboard->plainText(0);
	if(clipboard == 0)
	   pasteboard->dataObject()->setText(text);
}

void Pasteboard::setDragImage(DragImageRef, const IntPoint& hotSpot)
{
	D(bug("Pasteboard::setDragImage()\n"));
}

PassRefPtr<DocumentFragment> Pasteboard::documentFragment(Frame* frame, PassRefPtr<Range> context,
                                                          bool allowPlainText, bool& chosePlainText)
{
#warning "XXX: what to do here, exactly?"

	D(bug("Pasteboard::documentFragment() allowPlainText %d\n", allowPlainText));

	setWithClipboardContents(this, m_morphosClipboard);
	
	chosePlainText = false;

    if (m_dataObject->hasMarkup()) {
        RefPtr<DocumentFragment> fragment = createFragmentFromMarkup(frame->document(), m_dataObject->markup(), emptyString(), DisallowScriptingAndPluginContent);
        if (fragment)
            return fragment.release();
    }

    if (!allowPlainText)
        return 0;

    if (m_dataObject->hasText()) {
        chosePlainText = true;
        RefPtr<DocumentFragment> fragment = createFragmentFromText(context.get(), m_dataObject->text());
        if (fragment)
            return fragment.release();
    }

    return 0;
}

static void copycollection(String &str, CollectionItem* ci, uint32 codeSet)
{
    if (ci->ci_Next)
		copycollection(str, ci->ci_Next, codeSet);

	if (CODESET_UTF8 == codeSet)
	{
	    str.append(String::fromUTF8((const char *)ci->ci_Data, ci->ci_Size));
	}
	else if (CODESET_LOCAL == codeSet)
	{
		char *local = (char *) malloc(ci->ci_Size + 1);

		if(local)
		{
			char *converted;

			memcpy(local, (const char *) ci->ci_Data, ci->ci_Size);
			local[ci->ci_Size] = 0;

			converted = local_to_utf8(local);

			if(converted)
			{
			    str.append(String::fromUTF8(converted));
			    free(converted);
			}

			free(local);
		}
	}
}

String Pasteboard::plainText(Frame* frame)
{
	D(bug("Pasteboard::plainText()\n"));

    String result;

    if (IFFHandle *ih = AllocIFF()) {
        if (ClipboardHandle *ch = OpenClipboard(PRIMARY_CLIP)) {
            ih->iff_Stream = (uint32)ch;
            InitIFFasClip(ih);

            if (0 == OpenIFF(ih, IFFF_READ)) {
				const LONG chunks[4] = { ID_FTXT, ID_CHRS, ID_FTXT, ID_UTF8 };

                if (0 == CollectionChunks(ih, (LONG *)chunks, 2)
                 && 0 == StopOnExit(ih, ID_FTXT, ID_FORM))
                    while (true)
						if (IFFERR_EOC == ParseIFF(ih, IFFPARSE_SCAN))
						{
							CollectionItem *ci, *ci2;

							// First chunk is expected to have local charset
							ci = FindCollection(ih, ID_FTXT, ID_CHRS);

							// Second chunk is optional, and expected to have UTF8 charset if present
							ci2 = FindCollection(ih, ID_FTXT, ID_UTF8);

							if (ci2)
								copycollection(result, ci2, CODESET_UTF8);
							else if(ci)
								copycollection(result, ci, CODESET_LOCAL);
                        }
                        else
                            break;

                CloseIFF(ih);
            }
            CloseClipboard(ch);
        }
        FreeIFF(ih);
    }

    return result;

// XXX: use system or internal
/*
	return m_dataObject->text();
*/
}

bool Pasteboard::hasData()
{
	D(bug("Pasteboard::hasData()\n"));

	//setWithClipboardContents(this, m_morphosClipboard);

    return m_dataObject->hasText() || m_dataObject->hasMarkup() || m_dataObject->hasURIList() || m_dataObject->hasImage();
}

Vector<String> Pasteboard::types()
{
	D(bug("Pasteboard::types()\n"));

	setWithClipboardContents(this, m_morphosClipboard);

    Vector<String> types;
    if (m_dataObject->hasText()) {
        types.append(ASCIILiteral("text/plain"));
        types.append(ASCIILiteral("Text"));
        types.append(ASCIILiteral("text"));
    }

    if (m_dataObject->hasMarkup())
        types.append(ASCIILiteral("text/html"));

    if (m_dataObject->hasURIList()) {
        types.append(ASCIILiteral("text/uri-list"));
        types.append(ASCIILiteral("URL"));
    }

    if (m_dataObject->hasFilenames())
        types.append(ASCIILiteral("Files"));

    return types;
}

String Pasteboard::readString(const String& type)
{
	D(bug("Pasteboard::readString(%s)\n", type.utf8().data()));

	setWithClipboardContents(this, m_morphosClipboard);

    switch (dataObjectTypeFromHTMLClipboardType(type)) {
    case ClipboardDataTypeURIList:
        return m_dataObject->uriList();
    case ClipboardDataTypeURL:
        return m_dataObject->url();
    case ClipboardDataTypeMarkup:
        return m_dataObject->markup();
    case ClipboardDataTypeText:
        return m_dataObject->text();
    case ClipboardDataTypeImage:
    case ClipboardDataTypeUnknown:
        break;
    }

    return String();
}

Vector<String> Pasteboard::readFilenames()
{
	D(bug("Pasteboard::readFilenames()\n"));

	setWithClipboardContents(this, m_morphosClipboard);

    return m_dataObject->filenames();
}

}
