/**
 * Welcome to your Workbox-powered service worker!
 *
 * You'll need to register this file in your web app and you should
 * disable HTTP caching for this file too.
 * See https://goo.gl/nhQhGp
 *
 * The rest of the code is auto-generated. Please don't update this file
 * directly; instead, make changes to your Workbox build configuration
 * and re-run your build process.
 * See https://goo.gl/2aRDsh
 */

importScripts("https://storage.googleapis.com/workbox-cdn/releases/4.3.1/workbox-sw.js");

workbox.core.skipWaiting();

workbox.core.clientsClaim();

/**
 * The workboxSW.precacheAndRoute() method efficiently caches and responds to
 * requests for URLs in the manifest.
 * See https://goo.gl/S9QRab
 */
self.__precacheManifest = [
  {
    "url": "icons-192.a9c8c266.png",
    "revision": "5cb5b4a74dcc3c33b63be9684c16494b"
  },
  {
    "url": "icons-512.8aaa9830.png",
    "revision": "3ac3cac68a510323a0067aa0e6645cd3"
  },
  {
    "url": "index.html",
    "revision": "1640836d844518b57bb66f0a627cab6c"
  },
  {
    "url": "src.c0227ece.js",
    "revision": "59a74c09a2a2888d35cdea6f1a4f1972"
  },
  {
    "url": "style.d0cada05.css",
    "revision": "129c3d14b7c8d62da8cd4adabb41224a"
  },
  {
    "url": "/blend-sounds/",
    "revision": "25deeceac97c3d3a501cf918c4ba19df"
  }
].concat(self.__precacheManifest || []);
workbox.precaching.precacheAndRoute(self.__precacheManifest, {});

workbox.routing.registerNavigationRoute(workbox.precaching.getCacheKeyForURL("./index.html"));
