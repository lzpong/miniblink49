#ifndef RequestExtraData_h
#define RequestExtraData_h

#include "content/browser/WebPage.h"
#include "third_party/WebKit/public/platform/WebURLRequest.h"

namespace blink {
class WebLocalFrame;
}

#if (defined ENABLE_WKE) && (ENABLE_WKE == 1)
namespace content {
class WebPage;
}
#endif

namespace net {

class RequestExtraData : public blink::WebURLRequest::ExtraData {
public:
    virtual ~RequestExtraData() override
    {

    }

    blink::WebLocalFrame* getFrame()
    {
        if (!page)
            return nullptr;

        blink::WebFrame* frame = page->getWebFrameFromFrameId(m_frameId);
        if (!frame)
            return nullptr;

        if (!frame->isWebLocalFrame())
            return nullptr;

        return frame->toWebLocalFrame();
    }

    void setFrame(blink::WebLocalFrame* frame)
    {
        m_frameId = page->getFrameIdByBlinkFrame(reinterpret_cast<const blink::WebFrame*>(frame));
    }

private:
    //blink::WebLocalFrame* frame;
    int64_t m_frameId;

public:
#if (defined ENABLE_WKE) && (ENABLE_WKE == 1)
    content::WebPage* page;
#endif
};

} // net

#endif // RequestExtraData_h