

// function IsFCMember: check whether user is a member; use to suppress annoying popups etc.

function IsFCMember() {

        var is_member = 0;

        if (document.cookie.indexOf('fcmember') != -1) {

                is_member = 1;
        }

        return is_member;
}


function DisplayFCAdBanner() {

        if(FCWindowWidth > 400) {

		document.getElementById('fcnavbartable').style.visibility = "visible";

		if(FCWindowWidth >= 730) {

			// ZEDO for channel:  FC Member Content Head , publisher: FortuneCity.com , Ad Dimension: Super Banner - 728 x 90
			document.write('<script language="JavaScript">var zflag_nid="895"; var zflag_cid="51"; var zflag_sid="1"; var zflag_width="728"; var zflag_height="90"; var zflag_sz="14";</script><script language="JavaScript" src="http://d3.zedo.com/jsc/d3/fo.js"></script>');

		}

		else {
			document.getElementById('fcnavbartable').width = 468;

			// ZEDO for channel:  FC Member Content Head , publisher: FortuneCity.com , Ad Dimension: Full Banner - 468 x 60
			document.write('<script language="JavaScript">var zflag_nid="895"; var zflag_cid="51"; var zflag_sid="1"; var zflag_width="468"; var zflag_height="60"; var zflag_sz="0";</script><script language="JavaScript" src="http://d3.zedo.com/jsc/d3/fo.js"></script>');

			document.getElementById('fcnavbartable').width = 468;
		}
        }
}


function DisplayFCAdButtons() {

	if(fcadunit != 'adult') {

		if(FCWindowWidth > 700) {

			// ZEDO for channel:  FC Member Content Head , publisher: FortuneCity.com , Ad Dimension: Link Unit 728 - 728 x 15
			document.write('<script language="JavaScript">var zflag_nid="895"; var zflag_cid="51"; var zflag_sid="1"; var zflag_width="728"; var zflag_height="15"; var zflag_sz="18";</script><script language="JavaScript" src="http://d3.zedo.com/jsc/d3/fo.js"></script>');

		}

		else if(FCWindowWidth > 400) {

			// ZEDO for channel:  FC Member Content Head , publisher: FortuneCity.com , Ad Dimension: Link Unit 468 - 468 x 15
			document.write('<script language="JavaScript">var zflag_nid="895"; var zflag_cid="51"; var zflag_sid="1"; var zflag_width="468"; var zflag_height="15"; var zflag_sz="19";</script><script language="JavaScript" src="http://d3.zedo.com/jsc/d3/fo.js"></script>');

		}
	}
}


// now let's handle the exit popup

var showpopup = 0;

if (document.referrer.indexOf('.fortunecity.') == -1 && (!(document.referrer == null))){

        showpopup = 1;
}

if (document.referrer == '') {showpopup = 0;}  // weird kludge for 'view' from File Manager


if (navigator.appVersion.indexOf('MSIE') != -1 && navigator.appVersion.indexOf('Macintosh') != -1) {

                showpopup = 0;         // damn crappy IE/Mac
}


function MyExtendOnClick() {

	showpopup = 0;

        if (this.my_onclick != null) {

                this.my_onclick();
        }
}


function setonclickmethods() {

        if (navigator.appVersion.indexOf('MSIE') != -1 && navigator.appVersion.indexOf('Macintosh') != -1) {

                return;         // totally sucky
        }

	if(document.cookie.indexOf('fcseeninter') != -1 || IsFCMember() != 0 || fcadunit == 'adult') {

		return;		// only show interstitial once
	}

	this_domain = document.domain.substring(document.domain.indexOf('.'));

        for(i = 0; i < document.links.length; i++) {

                document.links[i].my_onclick = document.links[i].onclick;
        
                document.links[i].onclick = MyExtendOnClick;

		if(document.links[i].id.substring(0,2) != 'fc' &&
		document.links[i].href.toString().indexOf('mailto:') != 0 &&
		document.links[i].href.toString().indexOf('ftp:') != 0 &&
		document.links[i].href.toString().indexOf('news:') != 0) {	// don't break other protocols

// fix a nasty feature in IE whereby if the link text is in URL format, it gets the interstitial text
// prepended to it as well.  Note that these methods don't work in Netscape since the equivalent of
// link.innerText - link.text - is not settable, only gettable.  Luckily the problem doesn't arise in Firefox.
// First copy the existing value:

			if(navigator.userAgent.toString().indexOf('MSIE') != -1) {

				link_text_buffer = document.links[i].innerText.toString();
			}

// then do the normal prepend:

			document.links[i].href = 'http://www' + this_domain + '/banners/interstitial.html?' + document.links[i].href;

// then put the text back the way it was:

			if(navigator.userAgent.toString().indexOf('MSIE') != -1) {

				//document.links[i].innerText = link_text_buffer;
			}
		}
        }
}


function spawntopfivewindow() {

	if (showpopup == 1 && FCWindowWidth > 400 && IsFCMember() == 0 && document.cookie.indexOf('fcseeninter') == -1 && fcadunit != 'adult') {

		window.open('http://www.fortunecity.com/banners/exit.html','top5popup','toolbar=0,location=0,directories=0,status=0,menubar=0,scrollbars=1,resizable=1,width=820,height=610,left=0,top=0,screenX=0,screenY=0');

	}
}

