#include <unordered_map>
#include <string>

namespace http_server { 

namespace header {
    constexpr char* SHTML = "text/html";
    constexpr char* HTM = "text/html";
    constexpr char* HTML = "text/html";
    constexpr char* CSS = "text/css";
    constexpr char* XML = "text/xml";
    constexpr char* GIF = "image/gif";
    constexpr char* JPG = "image/jpeg";
    constexpr char* JPEG = "image/jpeg";
    constexpr char* JS = "application/javascript";
    constexpr char* ATOM = "application/atom+xml";
    constexpr char* RSS = "application/rss+xml";
    constexpr char* MML = "text/mathml";
    constexpr char* TXT = "text/plain";
    constexpr char* JAD = "text/vnd.sun.j2me.app-descriptor";
    constexpr char* WML = "text/vnd.wap.wml";
    constexpr char* HTC = "text/x-component";
    constexpr char* AVIF = "image/avif";
    constexpr char* PNG = "image/png";
    constexpr char* SVGZ = "image/svg+xml";
    constexpr char* SVG = "image/svg+xml";
    constexpr char* TIFF = "image/tiff";
    constexpr char* TIF = "image/tiff";
    constexpr char* WBMP = "image/vnd.wap.wbmp";
    constexpr char* WEBP = "image/webp";
    constexpr char* ICO = "image/x-icon";
    constexpr char* JNG = "image/x-jng";
    constexpr char* BMP = "image/x-ms-bmp";
    constexpr char* WOFF = "font/woff";
    constexpr char* WOFF2 = "font/woff2";
    constexpr char* JAVA_ARCHIVE = "application/java-archive";
    constexpr char* JSON = "application/json";
    constexpr char* MAC_BINHEX = "application/mac-binhex40";
    constexpr char* DOC = "application/msword";
    constexpr char* PDF = "application/pdf";
    constexpr char* POSTSCRIPT = "application/postscript";
    constexpr char* RTF = "application/rtf";
    constexpr char* MPEGURL = "application/vnd.apple.mpegurl";
    constexpr char* KML = "application/vnd.google-earth.kml+xml";
    constexpr char* KMZ = "application/vnd.google-earth.kmz";
    constexpr char* XLS = "application/vnd.ms-excel";
    constexpr char* EOT = "application/vnd.ms-fontobject";
    constexpr char* PPT = "application/vnd.ms-powerpoint";
    constexpr char* ODG = "application/vnd.oasis.opendocument.graphics";
    constexpr char* ODP = "application/vnd.oasis.opendocument.presentation";
    constexpr char* ODS = "application/vnd.oasis.opendocument.spreadsheet";
    constexpr char* ODT = "application/vnd.oasis.opendocument.text";
    constexpr char* PPTX = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    constexpr char* XLSX = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    constexpr char* DOCX = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    constexpr char* WMLC = "application/vnd.wap.wmlc";
    constexpr char* WASM = "application/wasm";
    constexpr char* COMPRESSED_7Z = "application/x-7z-compressed";
    constexpr char* COCOA = "application/x-cocoa";
    constexpr char* JARDIFF = "application/x-java-archive-diff";
    constexpr char* JNLP = "application/x-java-jnlp-file";
    constexpr char* MAKESELF = "application/x-makeself";
    constexpr char* PERL = "application/x-perl";
    constexpr char* PILOT = "application/x-pilot";
    constexpr char* RAR = "application/x-rar-compressed";
    constexpr char* RPM = "application/x-redhat-package-manager";
    constexpr char* SEA = "application/x-sea";
    constexpr char* SWF = "application/x-shockwave-flash";
    constexpr char* SIT = "application/x-stuffit";
    constexpr char* TCL = "application/x-tcl";
    constexpr char* X509 = "application/x-x509-ca-cert";
    constexpr char* XPI = "application/x-xpinstall";
    constexpr char* XHTML = "application/xhtml+xml";
    constexpr char* XSPF = "application/xspf+xml";
    constexpr char* ZIP = "application/zip";
    constexpr char* OCTET = "application/octet-stream";
    constexpr char* MIDI = "audio/midi";
    constexpr char* MPEG_AUDIO = "audio/mpeg";
    constexpr char* OGG = "audio/ogg";
    constexpr char* M4A = "audio/x-m4a";
    constexpr char* REALAUDIO = "audio/x-realaudio";
    constexpr char* VIDEO_3GPP = "video/3gpp";
    constexpr char* MP2T = "video/mp2t";
    constexpr char* MP4 = "video/mp4";
    constexpr char* MPEG_VIDEO = "video/mpeg";
    constexpr char* QUICKTIME = "video/quicktime";
    constexpr char* WEBM_VIDEO = "video/webm";
    constexpr char* FLV = "video/x-flv";
    constexpr char* M4V = "video/x-m4v";
    constexpr char* MNG = "video/x-mng";
    constexpr char* MS_ASF = "video/x-ms-asf";
    constexpr char* MS_WMV = "video/x-ms-wmv";
    constexpr char* MSVIDEO = "video/x-msvideo";
} // namespace header

} // namespace http_server
