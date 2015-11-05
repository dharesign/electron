// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_BROWSER_OBSERVER_H_
#define ATOM_BROWSER_BROWSER_OBSERVER_H_

#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/browser/client_certificate_delegate.h"

namespace content {
class WebContents;
}

namespace net {
class SSLCertRequestInfo;
class X509Certificate;
}

namespace atom {

class LoginHandler;

// A callback specialisation used by AtomCertVerifier during verification.
using CertificateVerifier =
    base::Callback<void(const std::string&,
                        scoped_refptr<net::X509Certificate>,
                        const base::Callback<void(bool)>&)>;

class BrowserObserver {
 public:
  // The browser is about to close all windows.
  virtual void OnBeforeQuit(bool* prevent_default) {}

  // The browser has closed all windows and will quit.
  virtual void OnWillQuit(bool* prevent_default) {}

  // The browser has closed all windows. If the browser is quiting, then this
  // method will not be called, instead it will call OnWillQuit.
  virtual void OnWindowAllClosed() {}

  // The browser is quitting.
  virtual void OnQuit() {}

  // The browser has opened a file by double clicking in Finder or dragging the
  // file to the Dock icon. (OS X only)
  virtual void OnOpenFile(bool* prevent_default,
                          const std::string& file_path) {}

  // Browser is used to open a url.
  virtual void OnOpenURL(const std::string& url) {}

  // The browser is activated with visible/invisible windows (usually by
  // clicking on the dock icon).
  virtual void OnActivate(bool has_visible_windows) {}

  // The browser has finished loading.
  virtual void OnWillFinishLaunching() {}
  virtual void OnFinishLaunching() {}

  // The browser requires client certificate.
  virtual void OnSelectCertificate(
      content::WebContents* web_contents,
      net::SSLCertRequestInfo* cert_request_info,
      scoped_ptr<content::ClientCertificateDelegate> delegate) {}

  // The browser requests HTTP login.
  virtual void OnLogin(LoginHandler* login_handler) {}

  virtual void OnSetCertificateVerifier(const CertificateVerifier& handler) {}
  virtual void OnRemoveCertificateVerifier() {}

 protected:
  virtual ~BrowserObserver() {}
};

}  // namespace atom

#endif  // ATOM_BROWSER_BROWSER_OBSERVER_H_
