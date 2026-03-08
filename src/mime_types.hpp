#pragma once

#include <unordered_map>
#include <string>

namespace http_server { 

namespace header {

namespace mime_types {
    constexpr const char* SHTML = "text/html";
    constexpr const char* HTM = "text/html";
    constexpr const char* HTML = "text/html";
    constexpr const char* CSS = "text/css";
    constexpr const char* XML = "text/xml";
    constexpr const char* GIF = "image/gif";
    constexpr const char* JPG = "image/jpeg";
    constexpr const char* JPEG = "image/jpeg";
    constexpr const char* JS = "application/javascript";
    constexpr const char* ATOM = "application/atom+xml";
    constexpr const char* RSS = "application/rss+xml";
    constexpr const char* MML = "text/mathml";
    constexpr const char* TXT = "text/plain";
    constexpr const char* JAD = "text/vnd.sun.j2me.app-descriptor";
    constexpr const char* WML = "text/vnd.wap.wml";
    constexpr const char* HTC = "text/x-component";
    constexpr const char* AVIF = "image/avif";
    constexpr const char* PNG = "image/png";
    constexpr const char* SVGZ = "image/svg+xml";
    constexpr const char* SVG = "image/svg+xml";
    constexpr const char* TIFF = "image/tiff";
    constexpr const char* TIF = "image/tiff";
    constexpr const char* WBMP = "image/vnd.wap.wbmp";
    constexpr const char* WEBP = "image/webp";
    constexpr const char* ICO = "image/x-icon";
    constexpr const char* JNG = "image/x-jng";
    constexpr const char* BMP = "image/x-ms-bmp";
    constexpr const char* WOFF = "font/woff";
    constexpr const char* WOFF2 = "font/woff2";
    constexpr const char* JAVA_ARCHIVE = "application/java-archive";
    constexpr const char* JSON = "application/json";
    constexpr const char* MAC_BINHEX = "application/mac-binhex40";
    constexpr const char* DOC = "application/msword";
    constexpr const char* PDF = "application/pdf";
    constexpr const char* POSTSCRIPT = "application/postscript";
    constexpr const char* RTF = "application/rtf";
    constexpr const char* MPEGURL = "application/vnd.apple.mpegurl";
    constexpr const char* KML = "application/vnd.google-earth.kml+xml";
    constexpr const char* KMZ = "application/vnd.google-earth.kmz";
    constexpr const char* XLS = "application/vnd.ms-excel";
    constexpr const char* EOT = "application/vnd.ms-fontobject";
    constexpr const char* PPT = "application/vnd.ms-powerpoint";
    constexpr const char* ODG = "application/vnd.oasis.opendocument.graphics";
    constexpr const char* ODP = "application/vnd.oasis.opendocument.presentation";
    constexpr const char* ODS = "application/vnd.oasis.opendocument.spreadsheet";
    constexpr const char* ODT = "application/vnd.oasis.opendocument.text";
    constexpr const char* PPTX = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    constexpr const char* XLSX = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    constexpr const char* DOCX = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    constexpr const char* WMLC = "application/vnd.wap.wmlc";
    constexpr const char* WASM = "application/wasm";
    constexpr const char* COMPRESSED_7Z = "application/x-7z-compressed";
    constexpr const char* COCOA = "application/x-cocoa";
    constexpr const char* JARDIFF = "application/x-java-archive-diff";
    constexpr const char* JNLP = "application/x-java-jnlp-file";
    constexpr const char* MAKESELF = "application/x-makeself";
    constexpr const char* PERL = "application/x-perl";
    constexpr const char* PILOT = "application/x-pilot";
    constexpr const char* RAR = "application/x-rar-compressed";
    constexpr const char* RPM = "application/x-redhat-package-manager";
    constexpr const char* SEA = "application/x-sea";
    constexpr const char* SWF = "application/x-shockwave-flash";
    constexpr const char* SIT = "application/x-stuffit";
    constexpr const char* TCL = "application/x-tcl";
    constexpr const char* X509 = "application/x-x509-ca-cert";
    constexpr const char* XPI = "application/x-xpinstall";
    constexpr const char* XHTML = "application/xhtml+xml";
    constexpr const char* XSPF = "application/xspf+xml";
    constexpr const char* ZIP = "application/zip";
    constexpr const char* OCTET = "application/octet-stream";
    constexpr const char* MIDI = "audio/midi";
    constexpr const char* MPEG_AUDIO = "audio/mpeg";
    constexpr const char* OGG = "audio/ogg";
    constexpr const char* M4A = "audio/x-m4a";
    constexpr const char* REALAUDIO = "audio/x-realaudio";
    constexpr const char* VIDEO_3GPP = "video/3gpp";
    constexpr const char* MP2T = "video/mp2t";
    constexpr const char* MP4 = "video/mp4";
    constexpr const char* MPEG_VIDEO = "video/mpeg";
    constexpr const char* QUICKTIME = "video/quicktime";
    constexpr const char* WEBM_VIDEO = "video/webm";
    constexpr const char* FLV = "video/x-flv";
    constexpr const char* M4V = "video/x-m4v";
    constexpr const char* MNG = "video/x-mng";
    constexpr const char* MS_ASF = "video/x-ms-asf";
    constexpr const char* MS_WMV = "video/x-ms-wmv";
    constexpr const char* MSVIDEO = "video/x-msvideo";
} // hamespace mime_types 

} // namespace header

} // namespace http_server
