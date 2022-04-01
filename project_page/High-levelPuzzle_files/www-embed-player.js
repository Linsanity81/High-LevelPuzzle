(function(){/*

 Copyright The Closure Library Authors.
 SPDX-License-Identifier: Apache-2.0
*/
'use strict';var l;function aa(a){var b=0;return function(){return b<a.length?{done:!1,value:a[b++]}:{done:!0}}}
var ba="function"==typeof Object.defineProperties?Object.defineProperty:function(a,b,c){if(a==Array.prototype||a==Object.prototype)return a;a[b]=c.value;return a};
function ca(a){a=["object"==typeof globalThis&&globalThis,a,"object"==typeof window&&window,"object"==typeof self&&self,"object"==typeof global&&global];for(var b=0;b<a.length;++b){var c=a[b];if(c&&c.Math==Math)return c}throw Error("Cannot find global object");}
var da=ca(this);function n(a,b){if(b)a:{var c=da;a=a.split(".");for(var d=0;d<a.length-1;d++){var e=a[d];if(!(e in c))break a;c=c[e]}a=a[a.length-1];d=c[a];b=b(d);b!=d&&null!=b&&ba(c,a,{configurable:!0,writable:!0,value:b})}}
n("Symbol",function(a){function b(f){if(this instanceof b)throw new TypeError("Symbol is not a constructor");return new c(d+(f||"")+"_"+e++,f)}
function c(f,g){this.h=f;ba(this,"description",{configurable:!0,writable:!0,value:g})}
if(a)return a;c.prototype.toString=function(){return this.h};
var d="jscomp_symbol_"+(1E9*Math.random()>>>0)+"_",e=0;return b});
n("Symbol.iterator",function(a){if(a)return a;a=Symbol("Symbol.iterator");for(var b="Array Int8Array Uint8Array Uint8ClampedArray Int16Array Uint16Array Int32Array Uint32Array Float32Array Float64Array".split(" "),c=0;c<b.length;c++){var d=da[b[c]];"function"===typeof d&&"function"!=typeof d.prototype[a]&&ba(d.prototype,a,{configurable:!0,writable:!0,value:function(){return ea(aa(this))}})}return a});
function ea(a){a={next:a};a[Symbol.iterator]=function(){return this};
return a}
function p(a){var b="undefined"!=typeof Symbol&&Symbol.iterator&&a[Symbol.iterator];return b?b.call(a):{next:aa(a)}}
function fa(a){if(!(a instanceof Array)){a=p(a);for(var b,c=[];!(b=a.next()).done;)c.push(b.value);a=c}return a}
function ha(a,b){return Object.prototype.hasOwnProperty.call(a,b)}
var ia="function"==typeof Object.assign?Object.assign:function(a,b){for(var c=1;c<arguments.length;c++){var d=arguments[c];if(d)for(var e in d)ha(d,e)&&(a[e]=d[e])}return a};
n("Object.assign",function(a){return a||ia});
var ja="function"==typeof Object.create?Object.create:function(a){function b(){}
b.prototype=a;return new b},la=function(){function a(){function c(){}
new c;Reflect.construct(c,[],function(){});
return new c instanceof c}
if("undefined"!=typeof Reflect&&Reflect.construct){if(a())return Reflect.construct;var b=Reflect.construct;return function(c,d,e){c=b(c,d);e&&Reflect.setPrototypeOf(c,e.prototype);return c}}return function(c,d,e){void 0===e&&(e=c);
e=ja(e.prototype||Object.prototype);return Function.prototype.apply.call(c,e,d)||e}}(),ma;
if("function"==typeof Object.setPrototypeOf)ma=Object.setPrototypeOf;else{var na;a:{var oa={a:!0},pa={};try{pa.__proto__=oa;na=pa.a;break a}catch(a){}na=!1}ma=na?function(a,b){a.__proto__=b;if(a.__proto__!==b)throw new TypeError(a+" is not extensible");return a}:null}var qa=ma;
function r(a,b){a.prototype=ja(b.prototype);a.prototype.constructor=a;if(qa)qa(a,b);else for(var c in b)if("prototype"!=c)if(Object.defineProperties){var d=Object.getOwnPropertyDescriptor(b,c);d&&Object.defineProperty(a,c,d)}else a[c]=b[c];a.aa=b.prototype}
function ra(){this.C=!1;this.l=null;this.i=void 0;this.h=1;this.o=this.m=0;this.A=this.j=null}
function sa(a){if(a.C)throw new TypeError("Generator is already running");a.C=!0}
ra.prototype.u=function(a){this.i=a};
function ta(a,b){a.j={ub:b,yb:!0};a.h=a.m||a.o}
ra.prototype.return=function(a){this.j={return:a};this.h=this.o};
function t(a,b,c){a.h=c;return{value:b}}
ra.prototype.s=function(a){this.h=a};
function wa(a,b,c){a.m=b;void 0!=c&&(a.o=c)}
function xa(a,b){a.h=b;a.m=0}
function ya(a){a.m=0;var b=a.j.ub;a.j=null;return b}
function za(a){a.A=[a.j];a.m=0;a.o=0}
function Aa(a){var b=a.A.splice(0)[0];(b=a.j=a.j||b)?b.yb?a.h=a.m||a.o:void 0!=b.s&&a.o<b.s?(a.h=b.s,a.j=null):a.h=a.o:a.h=0}
function Ba(a){this.h=new ra;this.i=a}
function Ea(a,b){sa(a.h);var c=a.h.l;if(c)return Fa(a,"return"in c?c["return"]:function(d){return{value:d,done:!0}},b,a.h.return);
a.h.return(b);return Ga(a)}
function Fa(a,b,c,d){try{var e=b.call(a.h.l,c);if(!(e instanceof Object))throw new TypeError("Iterator result "+e+" is not an object");if(!e.done)return a.h.C=!1,e;var f=e.value}catch(g){return a.h.l=null,ta(a.h,g),Ga(a)}a.h.l=null;d.call(a.h,f);return Ga(a)}
function Ga(a){for(;a.h.h;)try{var b=a.i(a.h);if(b)return a.h.C=!1,{value:b.value,done:!1}}catch(c){a.h.i=void 0,ta(a.h,c)}a.h.C=!1;if(a.h.j){b=a.h.j;a.h.j=null;if(b.yb)throw b.ub;return{value:b.return,done:!0}}return{value:void 0,done:!0}}
function Ha(a){this.next=function(b){sa(a.h);a.h.l?b=Fa(a,a.h.l.next,b,a.h.u):(a.h.u(b),b=Ga(a));return b};
this.throw=function(b){sa(a.h);a.h.l?b=Fa(a,a.h.l["throw"],b,a.h.u):(ta(a.h,b),b=Ga(a));return b};
this.return=function(b){return Ea(a,b)};
this[Symbol.iterator]=function(){return this}}
function Ia(a){function b(d){return a.next(d)}
function c(d){return a.throw(d)}
return new Promise(function(d,e){function f(g){g.done?d(g.value):Promise.resolve(g.value).then(b,c).then(f,e)}
f(a.next())})}
function w(a){return Ia(new Ha(new Ba(a)))}
function Ja(){for(var a=Number(this),b=[],c=a;c<arguments.length;c++)b[c-a]=arguments[c];return b}
n("Reflect",function(a){return a?a:{}});
n("Reflect.construct",function(){return la});
n("Reflect.setPrototypeOf",function(a){return a?a:qa?function(b,c){try{return qa(b,c),!0}catch(d){return!1}}:null});
n("Promise",function(a){function b(g){this.h=0;this.j=void 0;this.i=[];this.C=!1;var h=this.l();try{g(h.resolve,h.reject)}catch(k){h.reject(k)}}
function c(){this.h=null}
function d(g){return g instanceof b?g:new b(function(h){h(g)})}
if(a)return a;c.prototype.i=function(g){if(null==this.h){this.h=[];var h=this;this.j(function(){h.o()})}this.h.push(g)};
var e=da.setTimeout;c.prototype.j=function(g){e(g,0)};
c.prototype.o=function(){for(;this.h&&this.h.length;){var g=this.h;this.h=[];for(var h=0;h<g.length;++h){var k=g[h];g[h]=null;try{k()}catch(m){this.l(m)}}}this.h=null};
c.prototype.l=function(g){this.j(function(){throw g;})};
b.prototype.l=function(){function g(m){return function(q){k||(k=!0,m.call(h,q))}}
var h=this,k=!1;return{resolve:g(this.T),reject:g(this.o)}};
b.prototype.T=function(g){if(g===this)this.o(new TypeError("A Promise cannot resolve to itself"));else if(g instanceof b)this.fa(g);else{a:switch(typeof g){case "object":var h=null!=g;break a;case "function":h=!0;break a;default:h=!1}h?this.M(g):this.m(g)}};
b.prototype.M=function(g){var h=void 0;try{h=g.then}catch(k){this.o(k);return}"function"==typeof h?this.na(h,g):this.m(g)};
b.prototype.o=function(g){this.u(2,g)};
b.prototype.m=function(g){this.u(1,g)};
b.prototype.u=function(g,h){if(0!=this.h)throw Error("Cannot settle("+g+", "+h+"): Promise already settled in state"+this.h);this.h=g;this.j=h;2===this.h&&this.Y();this.A()};
b.prototype.Y=function(){var g=this;e(function(){if(g.L()){var h=da.console;"undefined"!==typeof h&&h.error(g.j)}},1)};
b.prototype.L=function(){if(this.C)return!1;var g=da.CustomEvent,h=da.Event,k=da.dispatchEvent;if("undefined"===typeof k)return!0;"function"===typeof g?g=new g("unhandledrejection",{cancelable:!0}):"function"===typeof h?g=new h("unhandledrejection",{cancelable:!0}):(g=da.document.createEvent("CustomEvent"),g.initCustomEvent("unhandledrejection",!1,!0,g));g.promise=this;g.reason=this.j;return k(g)};
b.prototype.A=function(){if(null!=this.i){for(var g=0;g<this.i.length;++g)f.i(this.i[g]);this.i=null}};
var f=new c;b.prototype.fa=function(g){var h=this.l();g.Ia(h.resolve,h.reject)};
b.prototype.na=function(g,h){var k=this.l();try{g.call(h,k.resolve,k.reject)}catch(m){k.reject(m)}};
b.prototype.then=function(g,h){function k(C,v){return"function"==typeof C?function(E){try{m(C(E))}catch(F){q(F)}}:v}
var m,q,u=new b(function(C,v){m=C;q=v});
this.Ia(k(g,m),k(h,q));return u};
b.prototype.catch=function(g){return this.then(void 0,g)};
b.prototype.Ia=function(g,h){function k(){switch(m.h){case 1:g(m.j);break;case 2:h(m.j);break;default:throw Error("Unexpected state: "+m.h);}}
var m=this;null==this.i?f.i(k):this.i.push(k);this.C=!0};
b.resolve=d;b.reject=function(g){return new b(function(h,k){k(g)})};
b.race=function(g){return new b(function(h,k){for(var m=p(g),q=m.next();!q.done;q=m.next())d(q.value).Ia(h,k)})};
b.all=function(g){var h=p(g),k=h.next();return k.done?d([]):new b(function(m,q){function u(E){return function(F){C[E]=F;v--;0==v&&m(C)}}
var C=[],v=0;do C.push(void 0),v++,d(k.value).Ia(u(C.length-1),q),k=h.next();while(!k.done)})};
return b});
n("WeakMap",function(a){function b(k){this.h=(h+=Math.random()+1).toString();if(k){k=p(k);for(var m;!(m=k.next()).done;)m=m.value,this.set(m[0],m[1])}}
function c(){}
function d(k){var m=typeof k;return"object"===m&&null!==k||"function"===m}
function e(k){if(!ha(k,g)){var m=new c;ba(k,g,{value:m})}}
function f(k){var m=Object[k];m&&(Object[k]=function(q){if(q instanceof c)return q;Object.isExtensible(q)&&e(q);return m(q)})}
if(function(){if(!a||!Object.seal)return!1;try{var k=Object.seal({}),m=Object.seal({}),q=new a([[k,2],[m,3]]);if(2!=q.get(k)||3!=q.get(m))return!1;q.delete(k);q.set(m,4);return!q.has(k)&&4==q.get(m)}catch(u){return!1}}())return a;
var g="$jscomp_hidden_"+Math.random();f("freeze");f("preventExtensions");f("seal");var h=0;b.prototype.set=function(k,m){if(!d(k))throw Error("Invalid WeakMap key");e(k);if(!ha(k,g))throw Error("WeakMap key fail: "+k);k[g][this.h]=m;return this};
b.prototype.get=function(k){return d(k)&&ha(k,g)?k[g][this.h]:void 0};
b.prototype.has=function(k){return d(k)&&ha(k,g)&&ha(k[g],this.h)};
b.prototype.delete=function(k){return d(k)&&ha(k,g)&&ha(k[g],this.h)?delete k[g][this.h]:!1};
return b});
n("Map",function(a){function b(){var h={};return h.previous=h.next=h.head=h}
function c(h,k){var m=h.h;return ea(function(){if(m){for(;m.head!=h.h;)m=m.previous;for(;m.next!=m.head;)return m=m.next,{done:!1,value:k(m)};m=null}return{done:!0,value:void 0}})}
function d(h,k){var m=k&&typeof k;"object"==m||"function"==m?f.has(k)?m=f.get(k):(m=""+ ++g,f.set(k,m)):m="p_"+k;var q=h.data_[m];if(q&&ha(h.data_,m))for(h=0;h<q.length;h++){var u=q[h];if(k!==k&&u.key!==u.key||k===u.key)return{id:m,list:q,index:h,entry:u}}return{id:m,list:q,index:-1,entry:void 0}}
function e(h){this.data_={};this.h=b();this.size=0;if(h){h=p(h);for(var k;!(k=h.next()).done;)k=k.value,this.set(k[0],k[1])}}
if(function(){if(!a||"function"!=typeof a||!a.prototype.entries||"function"!=typeof Object.seal)return!1;try{var h=Object.seal({x:4}),k=new a(p([[h,"s"]]));if("s"!=k.get(h)||1!=k.size||k.get({x:4})||k.set({x:4},"t")!=k||2!=k.size)return!1;var m=k.entries(),q=m.next();if(q.done||q.value[0]!=h||"s"!=q.value[1])return!1;q=m.next();return q.done||4!=q.value[0].x||"t"!=q.value[1]||!m.next().done?!1:!0}catch(u){return!1}}())return a;
var f=new WeakMap;e.prototype.set=function(h,k){h=0===h?0:h;var m=d(this,h);m.list||(m.list=this.data_[m.id]=[]);m.entry?m.entry.value=k:(m.entry={next:this.h,previous:this.h.previous,head:this.h,key:h,value:k},m.list.push(m.entry),this.h.previous.next=m.entry,this.h.previous=m.entry,this.size++);return this};
e.prototype.delete=function(h){h=d(this,h);return h.entry&&h.list?(h.list.splice(h.index,1),h.list.length||delete this.data_[h.id],h.entry.previous.next=h.entry.next,h.entry.next.previous=h.entry.previous,h.entry.head=null,this.size--,!0):!1};
e.prototype.clear=function(){this.data_={};this.h=this.h.previous=b();this.size=0};
e.prototype.has=function(h){return!!d(this,h).entry};
e.prototype.get=function(h){return(h=d(this,h).entry)&&h.value};
e.prototype.entries=function(){return c(this,function(h){return[h.key,h.value]})};
e.prototype.keys=function(){return c(this,function(h){return h.key})};
e.prototype.values=function(){return c(this,function(h){return h.value})};
e.prototype.forEach=function(h,k){for(var m=this.entries(),q;!(q=m.next()).done;)q=q.value,h.call(k,q[1],q[0],this)};
e.prototype[Symbol.iterator]=e.prototype.entries;var g=0;return e});
function Ka(a,b,c){if(null==a)throw new TypeError("The 'this' value for String.prototype."+c+" must not be null or undefined");if(b instanceof RegExp)throw new TypeError("First argument to String.prototype."+c+" must not be a regular expression");return a+""}
n("String.prototype.endsWith",function(a){return a?a:function(b,c){var d=Ka(this,b,"endsWith");b+="";void 0===c&&(c=d.length);c=Math.max(0,Math.min(c|0,d.length));for(var e=b.length;0<e&&0<c;)if(d[--c]!=b[--e])return!1;return 0>=e}});
n("Array.prototype.find",function(a){return a?a:function(b,c){a:{var d=this;d instanceof String&&(d=String(d));for(var e=d.length,f=0;f<e;f++){var g=d[f];if(b.call(c,g,f,d)){b=g;break a}}b=void 0}return b}});
n("String.prototype.startsWith",function(a){return a?a:function(b,c){var d=Ka(this,b,"startsWith");b+="";var e=d.length,f=b.length;c=Math.max(0,Math.min(c|0,d.length));for(var g=0;g<f&&c<e;)if(d[c++]!=b[g++])return!1;return g>=f}});
n("Number.isFinite",function(a){return a?a:function(b){return"number"!==typeof b?!1:!isNaN(b)&&Infinity!==b&&-Infinity!==b}});
function La(a,b){a instanceof String&&(a+="");var c=0,d=!1,e={next:function(){if(!d&&c<a.length){var f=c++;return{value:b(f,a[f]),done:!1}}d=!0;return{done:!0,value:void 0}}};
e[Symbol.iterator]=function(){return e};
return e}
n("Array.prototype.entries",function(a){return a?a:function(){return La(this,function(b,c){return[b,c]})}});
n("Object.setPrototypeOf",function(a){return a||qa});
n("Set",function(a){function b(c){this.h=new Map;if(c){c=p(c);for(var d;!(d=c.next()).done;)this.add(d.value)}this.size=this.h.size}
if(function(){if(!a||"function"!=typeof a||!a.prototype.entries||"function"!=typeof Object.seal)return!1;try{var c=Object.seal({x:4}),d=new a(p([c]));if(!d.has(c)||1!=d.size||d.add(c)!=d||1!=d.size||d.add({x:4})!=d||2!=d.size)return!1;var e=d.entries(),f=e.next();if(f.done||f.value[0]!=c||f.value[1]!=c)return!1;f=e.next();return f.done||f.value[0]==c||4!=f.value[0].x||f.value[1]!=f.value[0]?!1:e.next().done}catch(g){return!1}}())return a;
b.prototype.add=function(c){c=0===c?0:c;this.h.set(c,c);this.size=this.h.size;return this};
b.prototype.delete=function(c){c=this.h.delete(c);this.size=this.h.size;return c};
b.prototype.clear=function(){this.h.clear();this.size=0};
b.prototype.has=function(c){return this.h.has(c)};
b.prototype.entries=function(){return this.h.entries()};
b.prototype.values=function(){return this.h.values()};
b.prototype.keys=b.prototype.values;b.prototype[Symbol.iterator]=b.prototype.values;b.prototype.forEach=function(c,d){var e=this;this.h.forEach(function(f){return c.call(d,f,f,e)})};
return b});
n("Object.entries",function(a){return a?a:function(b){var c=[],d;for(d in b)ha(b,d)&&c.push([d,b[d]]);return c}});
n("Array.prototype.keys",function(a){return a?a:function(){return La(this,function(b){return b})}});
n("Array.prototype.values",function(a){return a?a:function(){return La(this,function(b,c){return c})}});
n("Object.is",function(a){return a?a:function(b,c){return b===c?0!==b||1/b===1/c:b!==b&&c!==c}});
n("Array.prototype.includes",function(a){return a?a:function(b,c){var d=this;d instanceof String&&(d=String(d));var e=d.length;c=c||0;for(0>c&&(c=Math.max(c+e,0));c<e;c++){var f=d[c];if(f===b||Object.is(f,b))return!0}return!1}});
n("String.prototype.includes",function(a){return a?a:function(b,c){return-1!==Ka(this,b,"includes").indexOf(b,c||0)}});
n("Number.isInteger",function(a){return a?a:function(b){return Number.isFinite(b)?b===Math.floor(b):!1}});
n("Array.from",function(a){return a?a:function(b,c,d){c=null!=c?c:function(h){return h};
var e=[],f="undefined"!=typeof Symbol&&Symbol.iterator&&b[Symbol.iterator];if("function"==typeof f){b=f.call(b);for(var g=0;!(f=b.next()).done;)e.push(c.call(d,f.value,g++))}else for(f=b.length,g=0;g<f;g++)e.push(c.call(d,b[g],g));return e}});
n("Number.isNaN",function(a){return a?a:function(b){return"number"===typeof b&&isNaN(b)}});
n("Number.MAX_SAFE_INTEGER",function(){return 9007199254740991});
n("Object.values",function(a){return a?a:function(b){var c=[],d;for(d in b)ha(b,d)&&c.push(b[d]);return c}});
var x=this||self;function y(a,b,c){a=a.split(".");c=c||x;a[0]in c||"undefined"==typeof c.execScript||c.execScript("var "+a[0]);for(var d;a.length&&(d=a.shift());)a.length||void 0===b?c[d]&&c[d]!==Object.prototype[d]?c=c[d]:c=c[d]={}:c[d]=b}
function z(a,b){a=a.split(".");b=b||x;for(var c=0;c<a.length;c++)if(b=b[a[c]],null==b)return null;return b}
function Ma(){}
function Na(a){a.cb=void 0;a.getInstance=function(){return a.cb?a.cb:a.cb=new a}}
function Pa(a){var b=typeof a;return"object"!=b?b:a?Array.isArray(a)?"array":b:"null"}
function Qa(a){var b=Pa(a);return"array"==b||"object"==b&&"number"==typeof a.length}
function Ra(a){var b=typeof a;return"object"==b&&null!=a||"function"==b}
function Sa(a){return Object.prototype.hasOwnProperty.call(a,Ta)&&a[Ta]||(a[Ta]=++Ua)}
var Ta="closure_uid_"+(1E9*Math.random()>>>0),Ua=0;function Va(a,b,c){return a.call.apply(a.bind,arguments)}
function Wa(a,b,c){if(!a)throw Error();if(2<arguments.length){var d=Array.prototype.slice.call(arguments,2);return function(){var e=Array.prototype.slice.call(arguments);Array.prototype.unshift.apply(e,d);return a.apply(b,e)}}return function(){return a.apply(b,arguments)}}
function Xa(a,b,c){Function.prototype.bind&&-1!=Function.prototype.bind.toString().indexOf("native code")?Xa=Va:Xa=Wa;return Xa.apply(null,arguments)}
function Ya(a,b){var c=Array.prototype.slice.call(arguments,1);return function(){var d=c.slice();d.push.apply(d,arguments);return a.apply(this,d)}}
function Za(a,b){function c(){}
c.prototype=b.prototype;a.aa=b.prototype;a.prototype=new c;a.prototype.constructor=a;a.Mo=function(d,e,f){for(var g=Array(arguments.length-2),h=2;h<arguments.length;h++)g[h-2]=arguments[h];return b.prototype[e].apply(d,g)}}
function $a(a){return a}
;function ab(a,b){if(Error.captureStackTrace)Error.captureStackTrace(this,ab);else{var c=Error().stack;c&&(this.stack=c)}a&&(this.message=String(a));void 0!==b&&(this.Ob=b)}
Za(ab,Error);ab.prototype.name="CustomError";function bb(a){a=a.url;var b=/[?&]dsh=1(&|$)/.test(a);this.j=!b&&/[?&]ae=1(&|$)/.test(a);this.l=!b&&/[?&]ae=2(&|$)/.test(a);if((this.h=/[?&]adurl=([^&]*)/.exec(a))&&this.h[1]){try{var c=decodeURIComponent(this.h[1])}catch(d){c=null}this.i=c}}
;function cb(){}
function db(a){var b=!1,c;return function(){b||(c=a(),b=!0);return c}}
;var eb=Array.prototype.indexOf?function(a,b){return Array.prototype.indexOf.call(a,b,void 0)}:function(a,b){if("string"===typeof a)return"string"!==typeof b||1!=b.length?-1:a.indexOf(b,0);
for(var c=0;c<a.length;c++)if(c in a&&a[c]===b)return c;return-1},fb=Array.prototype.forEach?function(a,b,c){Array.prototype.forEach.call(a,b,c)}:function(a,b,c){for(var d=a.length,e="string"===typeof a?a.split(""):a,f=0;f<d;f++)f in e&&b.call(c,e[f],f,a)},gb=Array.prototype.filter?function(a,b){return Array.prototype.filter.call(a,b,void 0)}:function(a,b){for(var c=a.length,d=[],e=0,f="string"===typeof a?a.split(""):a,g=0;g<c;g++)if(g in f){var h=f[g];
b.call(void 0,h,g,a)&&(d[e++]=h)}return d},hb=Array.prototype.map?function(a,b){return Array.prototype.map.call(a,b,void 0)}:function(a,b){for(var c=a.length,d=Array(c),e="string"===typeof a?a.split(""):a,f=0;f<c;f++)f in e&&(d[f]=b.call(void 0,e[f],f,a));
return d},ib=Array.prototype.reduce?function(a,b,c){return Array.prototype.reduce.call(a,b,c)}:function(a,b,c){var d=c;
fb(a,function(e,f){d=b.call(void 0,d,e,f,a)});
return d};
function jb(a,b){a:{for(var c=a.length,d="string"===typeof a?a.split(""):a,e=0;e<c;e++)if(e in d&&b.call(void 0,d[e],e,a)){b=e;break a}b=-1}return 0>b?null:"string"===typeof a?a.charAt(b):a[b]}
function kb(a,b){b=eb(a,b);var c;(c=0<=b)&&Array.prototype.splice.call(a,b,1);return c}
function lb(a,b){for(var c=1;c<arguments.length;c++){var d=arguments[c];if(Qa(d)){var e=a.length||0,f=d.length||0;a.length=e+f;for(var g=0;g<f;g++)a[e+g]=d[g]}else a.push(d)}}
;function mb(a,b){for(var c in a)b.call(void 0,a[c],c,a)}
function nb(a){var b=ob,c;for(c in b)if(a.call(void 0,b[c],c,b))return c}
function pb(a){for(var b in a)return!1;return!0}
function sb(a,b){if(null!==a&&b in a)throw Error('The object already contains the key "'+b+'"');a[b]=!0}
function tb(){var a=A("PLAYER_VARS",{});return null!==a&&"privembed"in a?a.privembed:!1}
function ub(a,b){for(var c in a)if(!(c in b)||a[c]!==b[c])return!1;for(var d in b)if(!(d in a))return!1;return!0}
function vb(a){var b={},c;for(c in a)b[c]=a[c];return b}
function wb(a){if(!a||"object"!==typeof a)return a;if("function"===typeof a.clone)return a.clone();if("undefined"!==typeof Map&&a instanceof Map)return new Map(a);if("undefined"!==typeof Set&&a instanceof Set)return new Set(a);var b=Array.isArray(a)?[]:"function"!==typeof ArrayBuffer||"function"!==typeof ArrayBuffer.isView||!ArrayBuffer.isView(a)||a instanceof DataView?{}:new a.constructor(a.length),c;for(c in a)b[c]=wb(a[c]);return b}
var xb="constructor hasOwnProperty isPrototypeOf propertyIsEnumerable toLocaleString toString valueOf".split(" ");function yb(a,b){for(var c,d,e=1;e<arguments.length;e++){d=arguments[e];for(c in d)a[c]=d[c];for(var f=0;f<xb.length;f++)c=xb[f],Object.prototype.hasOwnProperty.call(d,c)&&(a[c]=d[c])}}
;var zb;function Ab(){if(void 0===zb){var a=null,b=x.trustedTypes;if(b&&b.createPolicy){try{a=b.createPolicy("goog#html",{createHTML:$a,createScript:$a,createScriptURL:$a})}catch(c){x.console&&x.console.error(c.message)}zb=a}else zb=a}return zb}
;function Bb(a,b){this.j=a===Cb&&b||""}
Bb.prototype.i=!0;Bb.prototype.h=function(){return this.j};
function Db(a){return new Bb(Cb,a)}
var Cb={};Db("");var Eb={};function Fb(a){this.j=Eb===Eb?a:"";this.i=!0}
Fb.prototype.h=function(){return this.j.toString()};
Fb.prototype.toString=function(){return this.j.toString()};function Gb(a,b){this.j=b===Hb?a:""}
Gb.prototype.i=!0;Gb.prototype.h=function(){return this.j.toString()};
Gb.prototype.toString=function(){return this.j+""};
function Ib(a){if(a instanceof Gb&&a.constructor===Gb)return a.j;Pa(a);return"type_error:TrustedResourceUrl"}
var Hb={};function Lb(a){var b=Ab();a=b?b.createScriptURL(a):a;return new Gb(a,Hb)}
;var Mb=String.prototype.trim?function(a){return a.trim()}:function(a){return/^[\s\xa0]*([\s\S]*?)[\s\xa0]*$/.exec(a)[1]};function Nb(a,b){this.j=b===Ob?a:""}
Nb.prototype.i=!0;Nb.prototype.h=function(){return this.j.toString()};
Nb.prototype.toString=function(){return this.j.toString()};
function Pb(a){if(a instanceof Nb&&a.constructor===Nb)return a.j;Pa(a);return"type_error:SafeUrl"}
var Qb=/^(?:(?:https?|mailto|ftp):|[^:/?#]*(?:[/?#]|$))/i,Ob={};function Rb(){var a=x.navigator;return a&&(a=a.userAgent)?a:""}
function B(a){return-1!=Rb().indexOf(a)}
;function Sb(){return(B("Chrome")||B("CriOS"))&&!B("Edge")||B("Silk")}
;var Tb={};function Ub(a){this.j=Tb===Tb?a:"";this.i=!0}
Ub.prototype.h=function(){return this.j.toString()};
Ub.prototype.toString=function(){return this.j.toString()};function Vb(a,b){b instanceof Nb||b instanceof Nb||(b="object"==typeof b&&b.i?b.h():String(b),Qb.test(b)||(b="about:invalid#zClosurez"),b=new Nb(b,Ob));a.href=Pb(b)}
function Wb(a,b){a.rel="stylesheet";a.href=Ib(b).toString();(b=Xb('style[nonce],link[rel="stylesheet"][nonce]',a.ownerDocument&&a.ownerDocument.defaultView))&&a.setAttribute("nonce",b)}
function Yb(){return Xb("script[nonce]")}
var Zb=/^[\w+/_-]+[=]{0,2}$/;function Xb(a,b){b=(b||x).document;return b.querySelector?(a=b.querySelector(a))&&(a=a.nonce||a.getAttribute("nonce"))&&Zb.test(a)?a:"":""}
;function $b(a){for(var b=0,c=0;c<a.length;++c)b=31*b+a.charCodeAt(c)>>>0;return b}
;var ac=RegExp("^(?:([^:/?#.]+):)?(?://(?:([^\\\\/?#]*)@)?([^\\\\/?#]*?)(?::([0-9]+))?(?=[\\\\/?#]|$))?([^?#]+)?(?:\\?([^#]*))?(?:#([\\s\\S]*))?$");function bc(a){return a?decodeURI(a):a}
function cc(a,b){return b.match(ac)[a]||null}
function dc(a){return bc(cc(3,a))}
function ec(a){var b=a.match(ac);a=b[5];var c=b[6];b=b[7];var d="";a&&(d+=a);c&&(d+="?"+c);b&&(d+="#"+b);return d}
function fc(a,b,c){if(Array.isArray(b))for(var d=0;d<b.length;d++)fc(a,String(b[d]),c);else null!=b&&c.push(a+(""===b?"":"="+encodeURIComponent(String(b))))}
function gc(a){var b=[],c;for(c in a)fc(c,a[c],b);return b.join("&")}
function hc(a,b){b=gc(b);if(b){var c=a.indexOf("#");0>c&&(c=a.length);var d=a.indexOf("?");if(0>d||d>c){d=c;var e=""}else e=a.substring(d+1,c);a=[a.substr(0,d),e,a.substr(c)];c=a[1];a[1]=b?c?c+"&"+b:b:c;b=a[0]+(a[1]?"?"+a[1]:"")+a[2]}else b=a;return b}
function ic(a,b,c,d){for(var e=c.length;0<=(b=a.indexOf(c,b))&&b<d;){var f=a.charCodeAt(b-1);if(38==f||63==f)if(f=a.charCodeAt(b+e),!f||61==f||38==f||35==f)return b;b+=e+1}return-1}
var mc=/#|$/,nc=/[?&]($|#)/;function oc(a){for(var b=a.search(mc),c=0,d,e=[];0<=(d=ic(a,c,"key",b));)e.push(a.substring(c,d)),c=Math.min(a.indexOf("&",d)+1||b,b);e.push(a.substr(c));return e.join("").replace(nc,"$1")}
;function pc(){return B("iPhone")&&!B("iPod")&&!B("iPad")}
;function qc(a){qc[" "](a);return a}
qc[" "]=Ma;var rc=B("Opera"),sc=B("Trident")||B("MSIE"),tc=B("Edge"),uc=B("Gecko")&&!(-1!=Rb().toLowerCase().indexOf("webkit")&&!B("Edge"))&&!(B("Trident")||B("MSIE"))&&!B("Edge"),vc=-1!=Rb().toLowerCase().indexOf("webkit")&&!B("Edge"),wc=B("Android");function xc(){var a=x.document;return a?a.documentMode:void 0}
var yc;a:{var zc="",Ac=function(){var a=Rb();if(uc)return/rv:([^\);]+)(\)|;)/.exec(a);if(tc)return/Edge\/([\d\.]+)/.exec(a);if(sc)return/\b(?:MSIE|rv)[: ]([^\);]+)(\)|;)/.exec(a);if(vc)return/WebKit\/(\S+)/.exec(a);if(rc)return/(?:Version)[ \/]?(\S+)/.exec(a)}();
Ac&&(zc=Ac?Ac[1]:"");if(sc){var Bc=xc();if(null!=Bc&&Bc>parseFloat(zc)){yc=String(Bc);break a}}yc=zc}var Cc=yc,Dc;if(x.document&&sc){var Ec=xc();Dc=Ec?Ec:parseInt(Cc,10)||void 0}else Dc=void 0;var Fc=Dc;var Gc=pc()||B("iPod"),Hc=B("iPad");!B("Android")||Sb();Sb();var Ic=B("Safari")&&!(Sb()||B("Coast")||B("Opera")||B("Edge")||B("Edg/")||B("OPR")||B("Firefox")||B("FxiOS")||B("Silk")||B("Android"))&&!(pc()||B("iPad")||B("iPod"));var Jc={},Kc=null;
function Lc(a,b){Qa(a);void 0===b&&(b=0);if(!Kc){Kc={};for(var c="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789".split(""),d=["+/=","+/","-_=","-_.","-_"],e=0;5>e;e++){var f=c.concat(d[e].split(""));Jc[e]=f;for(var g=0;g<f.length;g++){var h=f[g];void 0===Kc[h]&&(Kc[h]=g)}}}b=Jc[b];c=Array(Math.floor(a.length/3));d=b[64]||"";for(e=f=0;f<a.length-2;f+=3){var k=a[f],m=a[f+1];h=a[f+2];g=b[k>>2];k=b[(k&3)<<4|m>>4];m=b[(m&15)<<2|h>>6];h=b[h&63];c[e++]=""+g+k+m+h}g=0;h=d;switch(a.length-
f){case 2:g=a[f+1],h=b[(g&15)<<2]||d;case 1:a=a[f],c[e]=""+b[a>>2]+b[(a&3)<<4|g>>4]+h+d}return c.join("")}
;var Mc="undefined"!==typeof Uint8Array;var Nc="function"===typeof Symbol&&"symbol"===typeof Symbol()?Symbol(void 0):void 0;function Oc(a,b){Object.isFrozen(a)||(Nc?a[Nc]|=b:void 0!==a.Ma?a.Ma|=b:Object.defineProperties(a,{Ma:{value:b,configurable:!0,writable:!0,enumerable:!1}}))}
function Pc(a){var b;Nc?b=a[Nc]:b=a.Ma;return null==b?0:b}
function Qc(a){Oc(a,1);return a}
function Rc(a){return Array.isArray(a)?!!(Pc(a)&2):!1}
function Sc(a){if(!Array.isArray(a))throw Error("cannot mark non-array as immutable");Oc(a,2)}
;function Tc(a){return null!==a&&"object"===typeof a&&!Array.isArray(a)&&a.constructor===Object}
var Uc,Vc=Object.freeze(Qc([]));function Wc(a){if(Rc(a.G))throw Error("Cannot mutate an immutable Message");}
var Xc="undefined"!=typeof Symbol&&"undefined"!=typeof Symbol.hasInstance;function ad(a){return{value:a,configurable:!1,writable:!1,enumerable:!1}}
;function bd(a){switch(typeof a){case "number":return isFinite(a)?a:String(a);case "object":if(a&&!Array.isArray(a)&&Mc&&null!=a&&a instanceof Uint8Array)return Lc(a)}return a}
;function cd(a,b){b=void 0===b?dd:b;return ed(a,b)}
function fd(a,b){if(null!=a){if(Array.isArray(a))a=ed(a,b);else if(Tc(a)){var c={},d;for(d in a)c[d]=fd(a[d],b);a=c}else a=b(a);return a}}
function ed(a,b){for(var c=a.slice(),d=0;d<c.length;d++)c[d]=fd(c[d],b);Array.isArray(a)&&Pc(a)&1&&Qc(c);return c}
function gd(a){if(a&&"object"==typeof a&&a.toJSON)return a.toJSON();a=bd(a);return Array.isArray(a)?cd(a,gd):a}
function dd(a){return Mc&&null!=a&&a instanceof Uint8Array?new Uint8Array(a):a}
;function hd(a,b,c){return-1===b?null:b>=a.l?a.i?a.i[b]:void 0:(void 0===c?0:c)&&a.i&&(c=a.i[b],null!=c)?c:a.G[b+a.j]}
function D(a,b,c,d,e){d=void 0===d?!1:d;(void 0===e?0:e)||Wc(a);b<a.l&&!d?a.G[b+a.j]=c:(a.i||(a.i=a.G[a.l+a.j]={}))[b]=c;return a}
function id(a,b,c,d){c=void 0===c?!0:c;d=void 0===d?!1:d;var e=hd(a,b,d);null==e&&(e=Vc);if(Rc(a.G))c&&(Sc(e),Object.freeze(e));else if(e===Vc||Rc(e))e=Qc(e.slice()),D(a,b,e,d);return e}
function jd(a,b,c,d){Wc(a);(c=kd(a,c))&&c!==b&&null!=d&&(a.h&&c in a.h&&(a.h[c]=void 0),D(a,c));return D(a,b,d)}
function kd(a,b){for(var c=0,d=0;d<b.length;d++){var e=b[d];null!=hd(a,e)&&(0!==c&&D(a,c,void 0,!1,!0),c=e)}return c}
function ld(a,b,c,d,e){if(-1===c)return null;a.h||(a.h={});var f=a.h[c];if(f)return f;e=hd(a,c,void 0===e?!1:e);if(null==e&&!d)return f;b=new b(e);Rc(a.G)&&Sc(b.G);return a.h[c]=b}
function md(a,b,c,d){d=void 0===d?!1:d;a.h||(a.h={});var e=Rc(a.G),f=a.h[c];if(!f){d=id(a,c,!0,d);f=[];e=e||Rc(d);for(var g=0;g<d.length;g++)f[g]=new b(d[g]),e&&Sc(f[g].G);e&&(Sc(f),Object.freeze(f));a.h[c]=f}return f}
function H(a,b,c,d){d=void 0===d?!1:d;Wc(a);a.h||(a.h={});var e=c?c.G:c;a.h[b]=c;return D(a,b,e,d)}
function nd(a,b,c,d){Wc(a);a.h||(a.h={});var e=d?d.G:d;a.h[b]=d;jd(a,b,c,e)}
function od(a,b,c,d){var e=void 0===e?!1:e;Wc(a);e=md(a,c,b,e);c=d?d:new c;a=id(a,b);e.push(c);a.push(c.G)}
function pd(a,b){a=hd(a,b);return null==a?"":a}
;function qd(a,b,c){a||(a=rd);rd=null;var d=this.constructor.i;a||(a=d?[d]:[]);this.j=(d?0:-1)-(this.constructor.h||0);this.h=void 0;this.G=a;a:{d=this.G.length;a=d-1;if(d&&(d=this.G[a],Tc(d))){this.l=a-this.j;this.i=d;break a}void 0!==b&&-1<b?(this.l=Math.max(b,a+1-this.j),this.i=void 0):this.l=Number.MAX_VALUE}if(c)for(b=0;b<c.length;b++)if(a=c[b],a<this.l)a+=this.j,(d=this.G[a])?Array.isArray(d)&&Qc(d):this.G[a]=Vc;else{d=this.i||(this.i=this.G[this.l+this.j]={});var e=d[a];e?Array.isArray(e)&&
Qc(e):d[a]=Vc}}
qd.prototype.toJSON=function(){var a=this.G;return Uc?a:cd(a,gd)};
function sd(a){Uc=!0;try{return JSON.stringify(a.toJSON(),td)}finally{Uc=!1}}
qd.prototype.clone=function(){var a=cd(this.G);rd=a;a=new this.constructor(a);rd=null;ud(a,this);return a};
qd.prototype.toString=function(){return this.G.toString()};
function td(a,b){return bd(b)}
function ud(a,b){b.o&&(a.o=b.o.slice());var c=b.h;if(c){b=b.i;for(var d in c){var e=c[d];if(e){var f=!(!b||!b[d]),g=+d;if(Array.isArray(e)){if(e.length)for(f=md(a,e[0].constructor,g,f),g=0;g<Math.min(f.length,e.length);g++)ud(f[g],e[g])}else(f=ld(a,e.constructor,g,void 0,f))&&ud(f,e)}}}}
var rd;function vd(){qd.apply(this,arguments)}
r(vd,qd);if(Xc){var wd={};Object.defineProperties(vd,(wd[Symbol.hasInstance]=ad(function(){throw Error("Cannot perform instanceof checks for MutableMessage");}),wd))};function xd(a,b){var c=this.h;if(this.isRepeated){var d=!0;d=void 0===d?!1:d;Wc(a);if(b){var e=Qc([]);for(var f=0;f<b.length;f++)e[f]=b[f].G;a.h||(a.h={});a.h[c]=b}else a.h&&(a.h[c]=void 0),e=Vc;a=D(a,c,e,d)}else a=H(a,c,b,!0);return a}
;function J(){vd.apply(this,arguments)}
r(J,vd);if(Xc){var yd={};Object.defineProperties(J,(yd[Symbol.hasInstance]=ad(Object[Symbol.hasInstance]),yd))};function zd(){var a=this;this.promise=new Promise(function(b,c){a.resolve=b;a.reject=c})}
;function Ad(a){this.i=!1;var b=a.program;a=a.globalName;var c=new zd;this.j=c.promise;this.l=p((0,x[a].a)(b,function(d,e){Promise.resolve().then(function(){c.resolve({Nb:d,wc:e})})},!0)).next().value;
this.vc=c.promise.then(function(){})}
Ad.prototype.snapshot=function(a){if(this.i)throw Error("Already disposed");return this.j.then(function(b){var c=b.Nb;return new Promise(function(d){c(function(e){d(e)},[a.pb,
a.xc])})})};
Ad.prototype.dispose=function(){this.i=!0;this.j.then(function(a){(a=a.wc)&&a()})};
Ad.prototype.h=function(){return this.i};var Bd=window;Db("csi.gstatic.com");Db("googleads.g.doubleclick.net");Db("partner.googleadservices.com");Db("pubads.g.doubleclick.net");Db("securepubads.g.doubleclick.net");Db("tpc.googlesyndication.com");/*

 SPDX-License-Identifier: Apache-2.0
*/
var Cd={};function Dd(){}
function Ed(a){this.h=a}
r(Ed,Dd);Ed.prototype.toString=function(){return this.h};
var Fd=new Ed("about:invalid#zTSz",Cd);function Gd(a){if(a instanceof Dd)if(a instanceof Ed)a=a.h;else throw Error("");else a=Pb(a);return a}
;function Hd(a,b){a.src=Ib(b);var c,d;(c=(b=null==(d=(c=(a.ownerDocument&&a.ownerDocument.defaultView||window).document).querySelector)?void 0:d.call(c,"script[nonce]"))?b.nonce||b.getAttribute("nonce")||"":"")&&a.setAttribute("nonce",c)}
;function Id(a,b){this.x=void 0!==a?a:0;this.y=void 0!==b?b:0}
l=Id.prototype;l.clone=function(){return new Id(this.x,this.y)};
l.equals=function(a){return a instanceof Id&&(this==a?!0:this&&a?this.x==a.x&&this.y==a.y:!1)};
l.ceil=function(){this.x=Math.ceil(this.x);this.y=Math.ceil(this.y);return this};
l.floor=function(){this.x=Math.floor(this.x);this.y=Math.floor(this.y);return this};
l.round=function(){this.x=Math.round(this.x);this.y=Math.round(this.y);return this};
l.scale=function(a,b){this.x*=a;this.y*="number"===typeof b?b:a;return this};function Jd(a,b){this.width=a;this.height=b}
l=Jd.prototype;l.clone=function(){return new Jd(this.width,this.height)};
l.aspectRatio=function(){return this.width/this.height};
l.isEmpty=function(){return!(this.width*this.height)};
l.ceil=function(){this.width=Math.ceil(this.width);this.height=Math.ceil(this.height);return this};
l.floor=function(){this.width=Math.floor(this.width);this.height=Math.floor(this.height);return this};
l.round=function(){this.width=Math.round(this.width);this.height=Math.round(this.height);return this};
l.scale=function(a,b){this.width*=a;this.height*="number"===typeof b?b:a;return this};function Kd(a){var b=document;return"string"===typeof a?b.getElementById(a):a}
function Ld(a){var b=document;a=String(a);"application/xhtml+xml"===b.contentType&&(a=a.toLowerCase());return b.createElement(a)}
function Md(a,b){for(var c=0;a;){if(b(a))return a;a=a.parentNode;c++}return null}
;function Nd(a){var b=Od;if(b)for(var c in b)Object.prototype.hasOwnProperty.call(b,c)&&a(b[c],c,b)}
function Pd(){var a=[];Nd(function(b){a.push(b)});
return a}
var Od={Oc:"allow-forms",Pc:"allow-modals",Qc:"allow-orientation-lock",Rc:"allow-pointer-lock",Sc:"allow-popups",Tc:"allow-popups-to-escape-sandbox",Uc:"allow-presentation",Vc:"allow-same-origin",Wc:"allow-scripts",Xc:"allow-top-navigation",Yc:"allow-top-navigation-by-user-activation"},Qd=db(function(){return Pd()});
function Rd(){var a=Sd(),b={};fb(Qd(),function(c){a.sandbox&&a.sandbox.supports&&a.sandbox.supports(c)&&(b[c]=!0)});
return b}
function Sd(){var a=void 0===a?document:a;return a.createElement("iframe")}
;function Td(a){this.isValid=a}
function Ud(a){return new Td(function(b){return b.substr(0,a.length+1).toLowerCase()===a+":"})}
var Vd=[Ud("data"),Ud("http"),Ud("https"),Ud("mailto"),Ud("ftp"),new Td(function(a){return/^[^:]*([/?#]|$)/.test(a)})];function Wd(a){"number"==typeof a&&(a=Math.round(a)+"px");return a}
;var $d=(new Date).getTime();function ae(a){if(!a)return"";if(/^about:(?:blank|srcdoc)$/.test(a))return window.origin||"";a=a.split("#")[0].split("?")[0];a=a.toLowerCase();0==a.indexOf("//")&&(a=window.location.protocol+a);/^[\w\-]*:\/\//.test(a)||(a=window.location.href);var b=a.substring(a.indexOf("://")+3),c=b.indexOf("/");-1!=c&&(b=b.substring(0,c));c=a.substring(0,a.indexOf("://"));if(!c)throw Error("URI is missing protocol: "+a);if("http"!==c&&"https"!==c&&"chrome-extension"!==c&&"moz-extension"!==c&&"file"!==c&&"android-app"!==
c&&"chrome-search"!==c&&"chrome-untrusted"!==c&&"chrome"!==c&&"app"!==c&&"devtools"!==c)throw Error("Invalid URI scheme in origin: "+c);a="";var d=b.indexOf(":");if(-1!=d){var e=b.substring(d+1);b=b.substring(0,d);if("http"===c&&"80"!==e||"https"===c&&"443"!==e)a=":"+e}return c+"://"+b+a}
;var be="client_dev_mss_url client_dev_regex_map client_dev_root_url client_rollout_override expflag jsfeat jsmode mods".split(" ");fa(be);function ce(){function a(){e[0]=1732584193;e[1]=4023233417;e[2]=2562383102;e[3]=271733878;e[4]=3285377520;q=m=0}
function b(u){for(var C=g,v=0;64>v;v+=4)C[v/4]=u[v]<<24|u[v+1]<<16|u[v+2]<<8|u[v+3];for(v=16;80>v;v++)u=C[v-3]^C[v-8]^C[v-14]^C[v-16],C[v]=(u<<1|u>>>31)&4294967295;u=e[0];var E=e[1],F=e[2],I=e[3],R=e[4];for(v=0;80>v;v++){if(40>v)if(20>v){var O=I^E&(F^I);var S=1518500249}else O=E^F^I,S=1859775393;else 60>v?(O=E&F|I&(E|F),S=2400959708):(O=E^F^I,S=3395469782);O=((u<<5|u>>>27)&4294967295)+O+R+S+C[v]&4294967295;R=I;I=F;F=(E<<30|E>>>2)&4294967295;E=u;u=O}e[0]=e[0]+u&4294967295;e[1]=e[1]+E&4294967295;e[2]=
e[2]+F&4294967295;e[3]=e[3]+I&4294967295;e[4]=e[4]+R&4294967295}
function c(u,C){if("string"===typeof u){u=unescape(encodeURIComponent(u));for(var v=[],E=0,F=u.length;E<F;++E)v.push(u.charCodeAt(E));u=v}C||(C=u.length);v=0;if(0==m)for(;v+64<C;)b(u.slice(v,v+64)),v+=64,q+=64;for(;v<C;)if(f[m++]=u[v++],q++,64==m)for(m=0,b(f);v+64<C;)b(u.slice(v,v+64)),v+=64,q+=64}
function d(){var u=[],C=8*q;56>m?c(h,56-m):c(h,64-(m-56));for(var v=63;56<=v;v--)f[v]=C&255,C>>>=8;b(f);for(v=C=0;5>v;v++)for(var E=24;0<=E;E-=8)u[C++]=e[v]>>E&255;return u}
for(var e=[],f=[],g=[],h=[128],k=1;64>k;++k)h[k]=0;var m,q;a();return{reset:a,update:c,digest:d,Rb:function(){for(var u=d(),C="",v=0;v<u.length;v++)C+="0123456789ABCDEF".charAt(Math.floor(u[v]/16))+"0123456789ABCDEF".charAt(u[v]%16);return C}}}
;function de(a,b,c){var d=String(x.location.href);return d&&a&&b?[b,ee(ae(d),a,c||null)].join(" "):null}
function ee(a,b,c){var d=[],e=[];if(1==(Array.isArray(c)?2:1))return e=[b,a],fb(d,function(h){e.push(h)}),fe(e.join(" "));
var f=[],g=[];fb(c,function(h){g.push(h.key);f.push(h.value)});
c=Math.floor((new Date).getTime()/1E3);e=0==f.length?[c,b,a]:[f.join(":"),c,b,a];fb(d,function(h){e.push(h)});
a=fe(e.join(" "));a=[c,a];0==g.length||a.push(g.join(""));return a.join("_")}
function fe(a){var b=ce();b.update(a);return b.Rb().toLowerCase()}
;var ge={};function he(a){this.h=a||{cookie:""}}
l=he.prototype;l.isEnabled=function(){if(!x.navigator.cookieEnabled)return!1;if(!this.isEmpty())return!0;this.set("TESTCOOKIESENABLED","1",{Oa:60});if("1"!==this.get("TESTCOOKIESENABLED"))return!1;this.remove("TESTCOOKIESENABLED");return!0};
l.set=function(a,b,c){var d=!1;if("object"===typeof c){var e=c.Yo;d=c.secure||!1;var f=c.domain||void 0;var g=c.path||void 0;var h=c.Oa}if(/[;=\s]/.test(a))throw Error('Invalid cookie name "'+a+'"');if(/[;\r\n]/.test(b))throw Error('Invalid cookie value "'+b+'"');void 0===h&&(h=-1);c=f?";domain="+f:"";g=g?";path="+g:"";d=d?";secure":"";h=0>h?"":0==h?";expires="+(new Date(1970,1,1)).toUTCString():";expires="+(new Date(Date.now()+1E3*h)).toUTCString();this.h.cookie=a+"="+b+c+g+h+d+(null!=e?";samesite="+
e:"")};
l.get=function(a,b){for(var c=a+"=",d=(this.h.cookie||"").split(";"),e=0,f;e<d.length;e++){f=Mb(d[e]);if(0==f.lastIndexOf(c,0))return f.substr(c.length);if(f==a)return""}return b};
l.remove=function(a,b,c){var d=void 0!==this.get(a);this.set(a,"",{Oa:0,path:b,domain:c});return d};
l.Ya=function(){return ie(this).keys};
l.isEmpty=function(){return!this.h.cookie};
l.clear=function(){for(var a=ie(this).keys,b=a.length-1;0<=b;b--)this.remove(a[b])};
function ie(a){a=(a.h.cookie||"").split(";");for(var b=[],c=[],d,e,f=0;f<a.length;f++)e=Mb(a[f]),d=e.indexOf("="),-1==d?(b.push(""),c.push(e)):(b.push(e.substring(0,d)),c.push(e.substring(d+1)));return{keys:b,values:c}}
var je=new he("undefined"==typeof document?null:document);function ke(a){return!!ge.FPA_SAMESITE_PHASE2_MOD||!(void 0===a||!a)}
function le(a){a=void 0===a?!1:a;var b=x.__SAPISID||x.__APISID||x.__3PSAPISID||x.__OVERRIDE_SID;ke(a)&&(b=b||x.__1PSAPISID);if(b)return!0;var c=new he(document);b=c.get("SAPISID")||c.get("APISID")||c.get("__Secure-3PAPISID")||c.get("SID");ke(a)&&(b=b||c.get("__Secure-1PAPISID"));return!!b}
function me(a,b,c,d){(a=x[a])||(a=(new he(document)).get(b));return a?de(a,c,d):null}
function ne(a){var b=void 0===b?!1:b;var c=ae(String(x.location.href)),d=[];if(le(b)){c=0==c.indexOf("https:")||0==c.indexOf("chrome-extension:")||0==c.indexOf("moz-extension:");var e=c?x.__SAPISID:x.__APISID;e||(e=new he(document),e=e.get(c?"SAPISID":"APISID")||e.get("__Secure-3PAPISID"));(e=e?de(e,c?"SAPISIDHASH":"APISIDHASH",a):null)&&d.push(e);c&&ke(b)&&((b=me("__1PSAPISID","__Secure-1PAPISID","SAPISID1PHASH",a))&&d.push(b),(a=me("__3PSAPISID","__Secure-3PAPISID","SAPISID3PHASH",a))&&d.push(a))}return 0==
d.length?null:d.join(" ")}
;function oe(a){if(Xc){var b={};Object.defineProperties(a,(b[Symbol.hasInstance]=ad(Object[Symbol.hasInstance]),b))}}
;function pe(a){a&&"function"==typeof a.dispose&&a.dispose()}
;function qe(a){for(var b=0,c=arguments.length;b<c;++b){var d=arguments[b];Qa(d)?qe.apply(null,d):pe(d)}}
;function K(){this.C=this.C;this.o=this.o}
K.prototype.C=!1;K.prototype.h=function(){return this.C};
K.prototype.dispose=function(){this.C||(this.C=!0,this.I())};
function re(a,b){a.C?b():(a.o||(a.o=[]),a.o.push(b))}
K.prototype.I=function(){if(this.o)for(;this.o.length;)this.o.shift()()};function se(a,b){this.type=a;this.h=this.target=b;this.defaultPrevented=this.j=!1}
se.prototype.stopPropagation=function(){this.j=!0};
se.prototype.preventDefault=function(){this.defaultPrevented=!0};function te(a){var b=z("window.location.href");null==a&&(a='Unknown Error of type "null/undefined"');if("string"===typeof a)return{message:a,name:"Unknown error",lineNumber:"Not available",fileName:b,stack:"Not available"};var c=!1;try{var d=a.lineNumber||a.line||"Not available"}catch(g){d="Not available",c=!0}try{var e=a.fileName||a.filename||a.sourceURL||x.$googDebugFname||b}catch(g){e="Not available",c=!0}b=ue(a);if(!(!c&&a.lineNumber&&a.fileName&&a.stack&&a.message&&a.name)){c=a.message;if(null==
c){if(a.constructor&&a.constructor instanceof Function){if(a.constructor.name)c=a.constructor.name;else if(c=a.constructor,ve[c])c=ve[c];else{c=String(c);if(!ve[c]){var f=/function\s+([^\(]+)/m.exec(c);ve[c]=f?f[1]:"[Anonymous]"}c=ve[c]}c='Unknown Error of type "'+c+'"'}else c="Unknown Error of unknown type";"function"===typeof a.toString&&Object.prototype.toString!==a.toString&&(c+=": "+a.toString())}return{message:c,name:a.name||"UnknownError",lineNumber:d,fileName:e,stack:b||"Not available"}}a.stack=
b;return{message:a.message,name:a.name,lineNumber:a.lineNumber,fileName:a.fileName,stack:a.stack}}
function ue(a,b){b||(b={});b[we(a)]=!0;var c=a.stack||"";(a=a.Ob)&&!b[we(a)]&&(c+="\nCaused by: ",a.stack&&0==a.stack.indexOf(a.toString())||(c+="string"===typeof a?a:a.message+"\n"),c+=ue(a,b));return c}
function we(a){var b="";"function"===typeof a.toString&&(b=""+a);return b+a.stack}
var ve={};var xe=function(){if(!x.addEventListener||!Object.defineProperty)return!1;var a=!1,b=Object.defineProperty({},"passive",{get:function(){a=!0}});
try{x.addEventListener("test",function(){},b),x.removeEventListener("test",function(){},b)}catch(c){}return a}();function ye(a,b){se.call(this,a?a.type:"");this.relatedTarget=this.h=this.target=null;this.button=this.screenY=this.screenX=this.clientY=this.clientX=0;this.key="";this.charCode=this.keyCode=0;this.metaKey=this.shiftKey=this.altKey=this.ctrlKey=!1;this.state=null;this.pointerId=0;this.pointerType="";this.i=null;a&&this.init(a,b)}
Za(ye,se);var ze={2:"touch",3:"pen",4:"mouse"};
ye.prototype.init=function(a,b){var c=this.type=a.type,d=a.changedTouches&&a.changedTouches.length?a.changedTouches[0]:null;this.target=a.target||a.srcElement;this.h=b;if(b=a.relatedTarget){if(uc){a:{try{qc(b.nodeName);var e=!0;break a}catch(f){}e=!1}e||(b=null)}}else"mouseover"==c?b=a.fromElement:"mouseout"==c&&(b=a.toElement);this.relatedTarget=b;d?(this.clientX=void 0!==d.clientX?d.clientX:d.pageX,this.clientY=void 0!==d.clientY?d.clientY:d.pageY,this.screenX=d.screenX||0,this.screenY=d.screenY||
0):(this.clientX=void 0!==a.clientX?a.clientX:a.pageX,this.clientY=void 0!==a.clientY?a.clientY:a.pageY,this.screenX=a.screenX||0,this.screenY=a.screenY||0);this.button=a.button;this.keyCode=a.keyCode||0;this.key=a.key||"";this.charCode=a.charCode||("keypress"==c?a.keyCode:0);this.ctrlKey=a.ctrlKey;this.altKey=a.altKey;this.shiftKey=a.shiftKey;this.metaKey=a.metaKey;this.pointerId=a.pointerId||0;this.pointerType="string"===typeof a.pointerType?a.pointerType:ze[a.pointerType]||"";this.state=a.state;
this.i=a;a.defaultPrevented&&ye.aa.preventDefault.call(this)};
ye.prototype.stopPropagation=function(){ye.aa.stopPropagation.call(this);this.i.stopPropagation?this.i.stopPropagation():this.i.cancelBubble=!0};
ye.prototype.preventDefault=function(){ye.aa.preventDefault.call(this);var a=this.i;a.preventDefault?a.preventDefault():a.returnValue=!1};var Ae="closure_listenable_"+(1E6*Math.random()|0);var Be=0;function Ce(a,b,c,d,e){this.listener=a;this.proxy=null;this.src=b;this.type=c;this.capture=!!d;this.La=e;this.key=++Be;this.ya=this.Ha=!1}
function De(a){a.ya=!0;a.listener=null;a.proxy=null;a.src=null;a.La=null}
;function Ee(a){this.src=a;this.listeners={};this.h=0}
Ee.prototype.add=function(a,b,c,d,e){var f=a.toString();a=this.listeners[f];a||(a=this.listeners[f]=[],this.h++);var g=Fe(a,b,d,e);-1<g?(b=a[g],c||(b.Ha=!1)):(b=new Ce(b,this.src,f,!!d,e),b.Ha=c,a.push(b));return b};
Ee.prototype.remove=function(a,b,c,d){a=a.toString();if(!(a in this.listeners))return!1;var e=this.listeners[a];b=Fe(e,b,c,d);return-1<b?(De(e[b]),Array.prototype.splice.call(e,b,1),0==e.length&&(delete this.listeners[a],this.h--),!0):!1};
function Ge(a,b){var c=b.type;c in a.listeners&&kb(a.listeners[c],b)&&(De(b),0==a.listeners[c].length&&(delete a.listeners[c],a.h--))}
function Fe(a,b,c,d){for(var e=0;e<a.length;++e){var f=a[e];if(!f.ya&&f.listener==b&&f.capture==!!c&&f.La==d)return e}return-1}
;var He="closure_lm_"+(1E6*Math.random()|0),Ie={},Je=0;function Ke(a,b,c,d,e){if(d&&d.once)Le(a,b,c,d,e);else if(Array.isArray(b))for(var f=0;f<b.length;f++)Ke(a,b[f],c,d,e);else c=Me(c),a&&a[Ae]?a.W(b,c,Ra(d)?!!d.capture:!!d,e):Ne(a,b,c,!1,d,e)}
function Ne(a,b,c,d,e,f){if(!b)throw Error("Invalid event type");var g=Ra(e)?!!e.capture:!!e,h=Oe(a);h||(a[He]=h=new Ee(a));c=h.add(b,c,d,g,f);if(!c.proxy){d=Pe();c.proxy=d;d.src=a;d.listener=c;if(a.addEventListener)xe||(e=g),void 0===e&&(e=!1),a.addEventListener(b.toString(),d,e);else if(a.attachEvent)a.attachEvent(Qe(b.toString()),d);else if(a.addListener&&a.removeListener)a.addListener(d);else throw Error("addEventListener and attachEvent are unavailable.");Je++}}
function Pe(){function a(c){return b.call(a.src,a.listener,c)}
var b=Re;return a}
function Le(a,b,c,d,e){if(Array.isArray(b))for(var f=0;f<b.length;f++)Le(a,b[f],c,d,e);else c=Me(c),a&&a[Ae]?a.l.add(String(b),c,!0,Ra(d)?!!d.capture:!!d,e):Ne(a,b,c,!0,d,e)}
function Se(a,b,c,d,e){if(Array.isArray(b))for(var f=0;f<b.length;f++)Se(a,b[f],c,d,e);else(d=Ra(d)?!!d.capture:!!d,c=Me(c),a&&a[Ae])?a.l.remove(String(b),c,d,e):a&&(a=Oe(a))&&(b=a.listeners[b.toString()],a=-1,b&&(a=Fe(b,c,d,e)),(c=-1<a?b[a]:null)&&Te(c))}
function Te(a){if("number"!==typeof a&&a&&!a.ya){var b=a.src;if(b&&b[Ae])Ge(b.l,a);else{var c=a.type,d=a.proxy;b.removeEventListener?b.removeEventListener(c,d,a.capture):b.detachEvent?b.detachEvent(Qe(c),d):b.addListener&&b.removeListener&&b.removeListener(d);Je--;(c=Oe(b))?(Ge(c,a),0==c.h&&(c.src=null,b[He]=null)):De(a)}}}
function Qe(a){return a in Ie?Ie[a]:Ie[a]="on"+a}
function Re(a,b){if(a.ya)a=!0;else{b=new ye(b,this);var c=a.listener,d=a.La||a.src;a.Ha&&Te(a);a=c.call(d,b)}return a}
function Oe(a){a=a[He];return a instanceof Ee?a:null}
var Ue="__closure_events_fn_"+(1E9*Math.random()>>>0);function Me(a){if("function"===typeof a)return a;a[Ue]||(a[Ue]=function(b){return a.handleEvent(b)});
return a[Ue]}
;function Ve(){K.call(this);this.l=new Ee(this);this.Y=this;this.L=null}
Za(Ve,K);Ve.prototype[Ae]=!0;Ve.prototype.addEventListener=function(a,b,c,d){Ke(this,a,b,c,d)};
Ve.prototype.removeEventListener=function(a,b,c,d){Se(this,a,b,c,d)};
function We(a,b){var c=a.L;if(c){var d=[];for(var e=1;c;c=c.L)d.push(c),++e}a=a.Y;c=b.type||b;"string"===typeof b?b=new se(b,a):b instanceof se?b.target=b.target||a:(e=b,b=new se(c,a),yb(b,e));e=!0;if(d)for(var f=d.length-1;!b.j&&0<=f;f--){var g=b.h=d[f];e=Xe(g,c,!0,b)&&e}b.j||(g=b.h=a,e=Xe(g,c,!0,b)&&e,b.j||(e=Xe(g,c,!1,b)&&e));if(d)for(f=0;!b.j&&f<d.length;f++)g=b.h=d[f],e=Xe(g,c,!1,b)&&e}
Ve.prototype.I=function(){Ve.aa.I.call(this);if(this.l){var a=this.l,b=0,c;for(c in a.listeners){for(var d=a.listeners[c],e=0;e<d.length;e++)++b,De(d[e]);delete a.listeners[c];a.h--}}this.L=null};
Ve.prototype.W=function(a,b,c,d){return this.l.add(String(a),b,!1,c,d)};
function Xe(a,b,c,d){b=a.l.listeners[String(b)];if(!b)return!0;b=b.concat();for(var e=!0,f=0;f<b.length;++f){var g=b[f];if(g&&!g.ya&&g.capture==c){var h=g.listener,k=g.La||g.src;g.Ha&&Ge(a.l,g);e=!1!==h.call(k,d)&&e}}return e&&!d.defaultPrevented}
;function Ye(a){Ve.call(this);var b=this;this.A=this.j=0;this.V=null!=a?a:{N:function(e,f){return setTimeout(e,f)},
U:clearTimeout};var c,d;this.i=null!=(d=null==(c=window.navigator)?void 0:c.onLine)?d:!0;this.m=function(){return w(function(e){return t(e,Ze(b),0)})};
window.addEventListener("offline",this.m);window.addEventListener("online",this.m);this.A||$e(this)}
r(Ye,Ve);function af(){var a=bf;Ye.h||(Ye.h=new Ye(a));return Ye.h}
Ye.prototype.dispose=function(){window.removeEventListener("offline",this.m);window.removeEventListener("online",this.m);this.V.U(this.A);delete Ye.h};
Ye.prototype.H=function(){return this.i};
function $e(a){a.A=a.V.N(function(){var b;return w(function(c){if(1==c.h)return a.i?(null==(b=window.navigator)?0:b.onLine)?c.s(3):t(c,Ze(a),3):t(c,Ze(a),3);$e(a);c.h=0})},3E4)}
function Ze(a,b){return a.u?a.u:a.u=new Promise(function(c){var d,e,f,g;return w(function(h){switch(h.h){case 1:return d=window.AbortController?new window.AbortController:void 0,f=null==(e=d)?void 0:e.signal,g=!1,wa(h,2,3),d&&(a.j=a.V.N(function(){d.abort()},b||2E4)),t(h,fetch("/generate_204",{method:"HEAD",
signal:f}),5);case 5:g=!0;case 3:za(h);a.u=void 0;a.j&&(a.V.U(a.j),a.j=0);g!==a.i&&(a.i=g,a.i?We(a,"networkstatus-online"):We(a,"networkstatus-offline"));c(g);Aa(h);break;case 2:ya(h),g=!1,h.s(3)}})})}
;var cf={wo:"WEB_DISPLAY_MODE_UNKNOWN",so:"WEB_DISPLAY_MODE_BROWSER",uo:"WEB_DISPLAY_MODE_MINIMAL_UI",vo:"WEB_DISPLAY_MODE_STANDALONE",to:"WEB_DISPLAY_MODE_FULLSCREEN"};function df(){this.data_=[];this.h=-1}
df.prototype.set=function(a,b){b=void 0===b?!0:b;0<=a&&52>a&&Number.isInteger(a)&&this.data_[a]!=b&&(this.data_[a]=b,this.h=-1)};
df.prototype.get=function(a){return!!this.data_[a]};
function ef(a){-1==a.h&&(a.h=ib(a.data_,function(b,c,d){return c?b+Math.pow(2,d):b},0));
return a.h}
;function ff(a,b){this.j=a;this.l=b;this.i=0;this.h=null}
ff.prototype.get=function(){if(0<this.i){this.i--;var a=this.h;this.h=a.next;a.next=null}else a=this.j();return a};
function gf(a,b){a.l(b);100>a.i&&(a.i++,b.next=a.h,a.h=b)}
;var hf;function jf(){var a=x.MessageChannel;"undefined"===typeof a&&"undefined"!==typeof window&&window.postMessage&&window.addEventListener&&!B("Presto")&&(a=function(){var e=Ld("IFRAME");e.style.display="none";document.documentElement.appendChild(e);var f=e.contentWindow;e=f.document;e.open();e.close();var g="callImmediate"+Math.random(),h="file:"==f.location.protocol?"*":f.location.protocol+"//"+f.location.host;e=Xa(function(k){if(("*"==h||k.origin==h)&&k.data==g)this.port1.onmessage()},this);
f.addEventListener("message",e,!1);this.port1={};this.port2={postMessage:function(){f.postMessage(g,h)}}});
if("undefined"!==typeof a&&!B("Trident")&&!B("MSIE")){var b=new a,c={},d=c;b.port1.onmessage=function(){if(void 0!==c.next){c=c.next;var e=c.nb;c.nb=null;e()}};
return function(e){d.next={nb:e};d=d.next;b.port2.postMessage(0)}}return function(e){x.setTimeout(e,0)}}
;function kf(a){x.setTimeout(function(){throw a;},0)}
;function lf(){this.i=this.h=null}
lf.prototype.add=function(a,b){var c=mf.get();c.set(a,b);this.i?this.i.next=c:this.h=c;this.i=c};
lf.prototype.remove=function(){var a=null;this.h&&(a=this.h,this.h=this.h.next,this.h||(this.i=null),a.next=null);return a};
var mf=new ff(function(){return new nf},function(a){return a.reset()});
function nf(){this.next=this.scope=this.h=null}
nf.prototype.set=function(a,b){this.h=a;this.scope=b;this.next=null};
nf.prototype.reset=function(){this.next=this.scope=this.h=null};function of(a,b){pf||qf();rf||(pf(),rf=!0);sf.add(a,b)}
var pf;function qf(){if(x.Promise&&x.Promise.resolve){var a=x.Promise.resolve(void 0);pf=function(){a.then(tf)}}else pf=function(){var b=tf;
"function"!==typeof x.setImmediate||x.Window&&x.Window.prototype&&!B("Edge")&&x.Window.prototype.setImmediate==x.setImmediate?(hf||(hf=jf()),hf(b)):x.setImmediate(b)}}
var rf=!1,sf=new lf;function tf(){for(var a;a=sf.remove();){try{a.h.call(a.scope)}catch(b){kf(b)}gf(mf,a)}rf=!1}
;function uf(a,b){this.h=a[x.Symbol.iterator]();this.i=b}
uf.prototype[Symbol.iterator]=function(){return this};
uf.prototype.next=function(){var a=this.h.next();return{value:a.done?void 0:this.i.call(void 0,a.value),done:a.done}};
function vf(a,b){return new uf(a,b)}
;function wf(){this.blockSize=-1}
;function xf(){this.blockSize=-1;this.blockSize=64;this.h=[];this.o=[];this.m=[];this.j=[];this.j[0]=128;for(var a=1;a<this.blockSize;++a)this.j[a]=0;this.l=this.i=0;this.reset()}
Za(xf,wf);xf.prototype.reset=function(){this.h[0]=1732584193;this.h[1]=4023233417;this.h[2]=2562383102;this.h[3]=271733878;this.h[4]=3285377520;this.l=this.i=0};
function yf(a,b,c){c||(c=0);var d=a.m;if("string"===typeof b)for(var e=0;16>e;e++)d[e]=b.charCodeAt(c)<<24|b.charCodeAt(c+1)<<16|b.charCodeAt(c+2)<<8|b.charCodeAt(c+3),c+=4;else for(e=0;16>e;e++)d[e]=b[c]<<24|b[c+1]<<16|b[c+2]<<8|b[c+3],c+=4;for(e=16;80>e;e++){var f=d[e-3]^d[e-8]^d[e-14]^d[e-16];d[e]=(f<<1|f>>>31)&4294967295}b=a.h[0];c=a.h[1];var g=a.h[2],h=a.h[3],k=a.h[4];for(e=0;80>e;e++){if(40>e)if(20>e){f=h^c&(g^h);var m=1518500249}else f=c^g^h,m=1859775393;else 60>e?(f=c&g|h&(c|g),m=2400959708):
(f=c^g^h,m=3395469782);f=(b<<5|b>>>27)+f+k+m+d[e]&4294967295;k=h;h=g;g=(c<<30|c>>>2)&4294967295;c=b;b=f}a.h[0]=a.h[0]+b&4294967295;a.h[1]=a.h[1]+c&4294967295;a.h[2]=a.h[2]+g&4294967295;a.h[3]=a.h[3]+h&4294967295;a.h[4]=a.h[4]+k&4294967295}
xf.prototype.update=function(a,b){if(null!=a){void 0===b&&(b=a.length);for(var c=b-this.blockSize,d=0,e=this.o,f=this.i;d<b;){if(0==f)for(;d<=c;)yf(this,a,d),d+=this.blockSize;if("string"===typeof a)for(;d<b;){if(e[f]=a.charCodeAt(d),++f,++d,f==this.blockSize){yf(this,e);f=0;break}}else for(;d<b;)if(e[f]=a[d],++f,++d,f==this.blockSize){yf(this,e);f=0;break}}this.i=f;this.l+=b}};
xf.prototype.digest=function(){var a=[],b=8*this.l;56>this.i?this.update(this.j,56-this.i):this.update(this.j,this.blockSize-(this.i-56));for(var c=this.blockSize-1;56<=c;c--)this.o[c]=b&255,b/=256;yf(this,this.o);for(c=b=0;5>c;c++)for(var d=24;0<=d;d-=8)a[b]=this.h[c]>>d&255,++b;return a};function zf(a){return"string"==typeof a.className?a.className:a.getAttribute&&a.getAttribute("class")||""}
function Af(a,b){"string"==typeof a.className?a.className=b:a.setAttribute&&a.setAttribute("class",b)}
function Bf(a,b){a.classList?b=a.classList.contains(b):(a=a.classList?a.classList:zf(a).match(/\S+/g)||[],b=0<=eb(a,b));return b}
function Cf(){var a=document.body;a.classList?a.classList.remove("inverted-hdpi"):Bf(a,"inverted-hdpi")&&Af(a,Array.prototype.filter.call(a.classList?a.classList:zf(a).match(/\S+/g)||[],function(b){return"inverted-hdpi"!=b}).join(" "))}
;function Df(){}
Df.prototype.next=function(){return Ef};
var Ef={done:!0,value:void 0};function Ff(a){return{value:a,done:!1}}
Df.prototype.Z=function(){return this};function Gf(a){if(a instanceof Hf||a instanceof If||a instanceof Jf)return a;if("function"==typeof a.next)return new Hf(function(){return a});
if("function"==typeof a[Symbol.iterator])return new Hf(function(){return a[Symbol.iterator]()});
if("function"==typeof a.Z)return new Hf(function(){return a.Z()});
throw Error("Not an iterator or iterable.");}
function Hf(a){this.i=a}
Hf.prototype.Z=function(){return new If(this.i())};
Hf.prototype[Symbol.iterator]=function(){return new Jf(this.i())};
Hf.prototype.h=function(){return new Jf(this.i())};
function If(a){this.i=a}
r(If,Df);If.prototype.next=function(){return this.i.next()};
If.prototype[Symbol.iterator]=function(){return new Jf(this.i)};
If.prototype.h=function(){return new Jf(this.i)};
function Jf(a){Hf.call(this,function(){return a});
this.j=a}
r(Jf,Hf);Jf.prototype.next=function(){return this.j.next()};function Kf(a,b){this.i={};this.h=[];this.ia=this.size=0;var c=arguments.length;if(1<c){if(c%2)throw Error("Uneven number of arguments");for(var d=0;d<c;d+=2)this.set(arguments[d],arguments[d+1])}else if(a)if(a instanceof Kf)for(c=a.Ya(),d=0;d<c.length;d++)this.set(c[d],a.get(c[d]));else for(d in a)this.set(d,a[d])}
l=Kf.prototype;l.Ya=function(){Lf(this);return this.h.concat()};
l.has=function(a){return Mf(this.i,a)};
l.equals=function(a,b){if(this===a)return!0;if(this.size!=a.size)return!1;b=b||Pf;Lf(this);for(var c,d=0;c=this.h[d];d++)if(!b(this.get(c),a.get(c)))return!1;return!0};
function Pf(a,b){return a===b}
l.isEmpty=function(){return 0==this.size};
l.clear=function(){this.i={};this.ia=this.size=this.h.length=0};
l.remove=function(a){return this.delete(a)};
l.delete=function(a){return Mf(this.i,a)?(delete this.i[a],--this.size,this.ia++,this.h.length>2*this.size&&Lf(this),!0):!1};
function Lf(a){if(a.size!=a.h.length){for(var b=0,c=0;b<a.h.length;){var d=a.h[b];Mf(a.i,d)&&(a.h[c++]=d);b++}a.h.length=c}if(a.size!=a.h.length){var e={};for(c=b=0;b<a.h.length;)d=a.h[b],Mf(e,d)||(a.h[c++]=d,e[d]=1),b++;a.h.length=c}}
l.get=function(a,b){return Mf(this.i,a)?this.i[a]:b};
l.set=function(a,b){Mf(this.i,a)||(this.size+=1,this.h.push(a),this.ia++);this.i[a]=b};
l.forEach=function(a,b){for(var c=this.Ya(),d=0;d<c.length;d++){var e=c[d],f=this.get(e);a.call(b,f,e,this)}};
l.clone=function(){return new Kf(this)};
l.keys=function(){return Gf(this.Z(!0)).h()};
l.values=function(){return Gf(this.Z(!1)).h()};
l.entries=function(){var a=this;return vf(this.keys(),function(b){return[b,a.get(b)]})};
l.Z=function(a){Lf(this);var b=0,c=this.ia,d=this,e=new Df;e.next=function(){if(c!=d.ia)throw Error("The map has changed since the iterator was created");if(b>=d.h.length)return Ef;var f=d.h[b++];return Ff(a?f:d.i[f])};
return e};
function Mf(a,b){return Object.prototype.hasOwnProperty.call(a,b)}
;function Qf(a){var b=[];Rf(new Sf,a,b);return b.join("")}
function Sf(){}
function Rf(a,b,c){if(null==b)c.push("null");else{if("object"==typeof b){if(Array.isArray(b)){var d=b;b=d.length;c.push("[");for(var e="",f=0;f<b;f++)c.push(e),Rf(a,d[f],c),e=",";c.push("]");return}if(b instanceof String||b instanceof Number||b instanceof Boolean)b=b.valueOf();else{c.push("{");e="";for(d in b)Object.prototype.hasOwnProperty.call(b,d)&&(f=b[d],"function"!=typeof f&&(c.push(e),Tf(d,c),c.push(":"),Rf(a,f,c),e=","));c.push("}");return}}switch(typeof b){case "string":Tf(b,c);break;case "number":c.push(isFinite(b)&&
!isNaN(b)?String(b):"null");break;case "boolean":c.push(String(b));break;case "function":c.push("null");break;default:throw Error("Unknown type: "+typeof b);}}}
var Uf={'"':'\\"',"\\":"\\\\","/":"\\/","\b":"\\b","\f":"\\f","\n":"\\n","\r":"\\r","\t":"\\t","\v":"\\u000b"},Vf=/\uffff/.test("\uffff")?/[\\"\x00-\x1f\x7f-\uffff]/g:/[\\"\x00-\x1f\x7f-\xff]/g;function Tf(a,b){b.push('"',a.replace(Vf,function(c){var d=Uf[c];d||(d="\\u"+(c.charCodeAt(0)|65536).toString(16).substr(1),Uf[c]=d);return d}),'"')}
;function Wf(a){if(!a)return!1;try{return!!a.$goog_Thenable}catch(b){return!1}}
;function Xf(a){this.h=0;this.C=void 0;this.l=this.i=this.j=null;this.o=this.m=!1;if(a!=cb)try{var b=this;a.call(void 0,function(c){Yf(b,2,c)},function(c){Yf(b,3,c)})}catch(c){Yf(this,3,c)}}
function Zf(){this.next=this.context=this.onRejected=this.i=this.h=null;this.j=!1}
Zf.prototype.reset=function(){this.context=this.onRejected=this.i=this.h=null;this.j=!1};
var $f=new ff(function(){return new Zf},function(a){a.reset()});
function ag(a,b,c){var d=$f.get();d.i=a;d.onRejected=b;d.context=c;return d}
function bg(a){return new Xf(function(b,c){c(a)})}
Xf.prototype.then=function(a,b,c){return cg(this,"function"===typeof a?a:null,"function"===typeof b?b:null,c)};
Xf.prototype.$goog_Thenable=!0;function dg(a,b){return cg(a,null,b)}
Xf.prototype.cancel=function(a){if(0==this.h){var b=new eg(a);of(function(){fg(this,b)},this)}};
function fg(a,b){if(0==a.h)if(a.j){var c=a.j;if(c.i){for(var d=0,e=null,f=null,g=c.i;g&&(g.j||(d++,g.h==a&&(e=g),!(e&&1<d)));g=g.next)e||(f=g);e&&(0==c.h&&1==d?fg(c,b):(f?(d=f,d.next==c.l&&(c.l=d),d.next=d.next.next):gg(c),hg(c,e,3,b)))}a.j=null}else Yf(a,3,b)}
function ig(a,b){a.i||2!=a.h&&3!=a.h||jg(a);a.l?a.l.next=b:a.i=b;a.l=b}
function cg(a,b,c,d){var e=ag(null,null,null);e.h=new Xf(function(f,g){e.i=b?function(h){try{var k=b.call(d,h);f(k)}catch(m){g(m)}}:f;
e.onRejected=c?function(h){try{var k=c.call(d,h);void 0===k&&h instanceof eg?g(h):f(k)}catch(m){g(m)}}:g});
e.h.j=a;ig(a,e);return e.h}
Xf.prototype.A=function(a){this.h=0;Yf(this,2,a)};
Xf.prototype.L=function(a){this.h=0;Yf(this,3,a)};
function Yf(a,b,c){if(0==a.h){a===c&&(b=3,c=new TypeError("Promise cannot resolve to itself"));a.h=1;a:{var d=c,e=a.A,f=a.L;if(d instanceof Xf){ig(d,ag(e||cb,f||null,a));var g=!0}else if(Wf(d))d.then(e,f,a),g=!0;else{if(Ra(d))try{var h=d.then;if("function"===typeof h){kg(d,h,e,f,a);g=!0;break a}}catch(k){f.call(a,k);g=!0;break a}g=!1}}g||(a.C=c,a.h=b,a.j=null,jg(a),3!=b||c instanceof eg||lg(a,c))}}
function kg(a,b,c,d,e){function f(k){h||(h=!0,d.call(e,k))}
function g(k){h||(h=!0,c.call(e,k))}
var h=!1;try{b.call(a,g,f)}catch(k){f(k)}}
function jg(a){a.m||(a.m=!0,of(a.u,a))}
function gg(a){var b=null;a.i&&(b=a.i,a.i=b.next,b.next=null);a.i||(a.l=null);return b}
Xf.prototype.u=function(){for(var a;a=gg(this);)hg(this,a,this.h,this.C);this.m=!1};
function hg(a,b,c,d){if(3==c&&b.onRejected&&!b.j)for(;a&&a.o;a=a.j)a.o=!1;if(b.h)b.h.j=null,mg(b,c,d);else try{b.j?b.i.call(b.context):mg(b,c,d)}catch(e){ng.call(null,e)}gf($f,b)}
function mg(a,b,c){2==b?a.i.call(a.context,c):a.onRejected&&a.onRejected.call(a.context,c)}
function lg(a,b){a.o=!0;of(function(){a.o&&ng.call(null,b)})}
var ng=kf;function eg(a){ab.call(this,a)}
Za(eg,ab);eg.prototype.name="cancel";function L(a){K.call(this);this.u=1;this.l=[];this.m=0;this.i=[];this.j={};this.A=!!a}
Za(L,K);l=L.prototype;l.subscribe=function(a,b,c){var d=this.j[a];d||(d=this.j[a]=[]);var e=this.u;this.i[e]=a;this.i[e+1]=b;this.i[e+2]=c;this.u=e+3;d.push(e);return e};
function og(a,b,c,d){if(b=a.j[b]){var e=a.i;(b=b.find(function(f){return e[f+1]==c&&e[f+2]==d}))&&a.ta(b)}}
l.ta=function(a){var b=this.i[a];if(b){var c=this.j[b];0!=this.m?(this.l.push(a),this.i[a+1]=Ma):(c&&kb(c,a),delete this.i[a],delete this.i[a+1],delete this.i[a+2])}return!!b};
l.ja=function(a,b){var c=this.j[a];if(c){for(var d=Array(arguments.length-1),e=1,f=arguments.length;e<f;e++)d[e-1]=arguments[e];if(this.A)for(e=0;e<c.length;e++){var g=c[e];pg(this.i[g+1],this.i[g+2],d)}else{this.m++;try{for(e=0,f=c.length;e<f&&!this.h();e++)g=c[e],this.i[g+1].apply(this.i[g+2],d)}finally{if(this.m--,0<this.l.length&&0==this.m)for(;c=this.l.pop();)this.ta(c)}}return 0!=e}return!1};
function pg(a,b,c){of(function(){a.apply(b,c)})}
l.clear=function(a){if(a){var b=this.j[a];b&&(b.forEach(this.ta,this),delete this.j[a])}else this.i.length=0,this.j={}};
l.I=function(){L.aa.I.call(this);this.clear();this.l.length=0};function qg(a){this.h=a}
qg.prototype.set=function(a,b){void 0===b?this.h.remove(a):this.h.set(a,Qf(b))};
qg.prototype.get=function(a){try{var b=this.h.get(a)}catch(c){return}if(null!==b)try{return JSON.parse(b)}catch(c){throw"Storage: Invalid value was encountered";}};
qg.prototype.remove=function(a){this.h.remove(a)};function rg(a){this.h=a}
Za(rg,qg);function sg(a){this.data=a}
function tg(a){return void 0===a||a instanceof sg?a:new sg(a)}
rg.prototype.set=function(a,b){rg.aa.set.call(this,a,tg(b))};
rg.prototype.i=function(a){a=rg.aa.get.call(this,a);if(void 0===a||a instanceof Object)return a;throw"Storage: Invalid value was encountered";};
rg.prototype.get=function(a){if(a=this.i(a)){if(a=a.data,void 0===a)throw"Storage: Invalid value was encountered";}else a=void 0;return a};function ug(a){this.h=a}
Za(ug,rg);ug.prototype.set=function(a,b,c){if(b=tg(b)){if(c){if(c<Date.now()){ug.prototype.remove.call(this,a);return}b.expiration=c}b.creation=Date.now()}ug.aa.set.call(this,a,b)};
ug.prototype.i=function(a){var b=ug.aa.i.call(this,a);if(b){var c=b.creation,d=b.expiration;if(d&&d<Date.now()||c&&c>Date.now())ug.prototype.remove.call(this,a);else return b}};function vg(){}
;function wg(){}
Za(wg,vg);wg.prototype[Symbol.iterator]=function(){return Gf(this.Z(!0)).h()};
wg.prototype.clear=function(){var a=Array.from(this);a=p(a);for(var b=a.next();!b.done;b=a.next())this.remove(b.value)};function xg(a){this.h=a}
Za(xg,wg);l=xg.prototype;l.isAvailable=function(){if(!this.h)return!1;try{return this.h.setItem("__sak","1"),this.h.removeItem("__sak"),!0}catch(a){return!1}};
l.set=function(a,b){try{this.h.setItem(a,b)}catch(c){if(0==this.h.length)throw"Storage mechanism: Storage disabled";throw"Storage mechanism: Quota exceeded";}};
l.get=function(a){a=this.h.getItem(a);if("string"!==typeof a&&null!==a)throw"Storage mechanism: Invalid value was encountered";return a};
l.remove=function(a){this.h.removeItem(a)};
l.Z=function(a){var b=0,c=this.h,d=new Df;d.next=function(){if(b>=c.length)return Ef;var e=c.key(b++);if(a)return Ff(e);e=c.getItem(e);if("string"!==typeof e)throw"Storage mechanism: Invalid value was encountered";return Ff(e)};
return d};
l.clear=function(){this.h.clear()};
l.key=function(a){return this.h.key(a)};function yg(){var a=null;try{a=window.localStorage||null}catch(b){}this.h=a}
Za(yg,xg);function zg(a,b){this.i=a;this.h=null;var c;if(c=sc)c=!(9<=Number(Fc));if(c){Ag||(Ag=new Kf);this.h=Ag.get(a);this.h||(b?this.h=document.getElementById(b):(this.h=document.createElement("userdata"),this.h.addBehavior("#default#userData"),document.body.appendChild(this.h)),Ag.set(a,this.h));try{this.h.load(this.i)}catch(d){this.h=null}}}
Za(zg,wg);var Bg={".":".2E","!":".21","~":".7E","*":".2A","'":".27","(":".28",")":".29","%":"."},Ag=null;function Cg(a){return"_"+encodeURIComponent(a).replace(/[.!~*'()%]/g,function(b){return Bg[b]})}
l=zg.prototype;l.isAvailable=function(){return!!this.h};
l.set=function(a,b){this.h.setAttribute(Cg(a),b);Dg(this)};
l.get=function(a){a=this.h.getAttribute(Cg(a));if("string"!==typeof a&&null!==a)throw"Storage mechanism: Invalid value was encountered";return a};
l.remove=function(a){this.h.removeAttribute(Cg(a));Dg(this)};
l.Z=function(a){var b=0,c=this.h.XMLDocument.documentElement.attributes,d=new Df;d.next=function(){if(b>=c.length)return Ef;var e=c[b++];if(a)return Ff(decodeURIComponent(e.nodeName.replace(/\./g,"%")).substr(1));e=e.nodeValue;if("string"!==typeof e)throw"Storage mechanism: Invalid value was encountered";return Ff(e)};
return d};
l.clear=function(){for(var a=this.h.XMLDocument.documentElement,b=a.attributes.length;0<b;b--)a.removeAttribute(a.attributes[b-1].nodeName);Dg(this)};
function Dg(a){try{a.h.save(a.i)}catch(b){throw"Storage mechanism: Quota exceeded";}}
;function Eg(a,b){this.i=a;this.h=b+"::"}
Za(Eg,wg);Eg.prototype.set=function(a,b){this.i.set(this.h+a,b)};
Eg.prototype.get=function(a){return this.i.get(this.h+a)};
Eg.prototype.remove=function(a){this.i.remove(this.h+a)};
Eg.prototype.Z=function(a){var b=this.i[Symbol.iterator](),c=this,d=new Df;d.next=function(){var e=b.next();if(e.done)return e;for(e=e.value;e.substr(0,c.h.length)!=c.h;){e=b.next();if(e.done)return e;e=e.value}return Ff(a?e.substr(c.h.length):c.i.get(e))};
return d};function Fg(a){J.call(this,a)}
r(Fg,J);Fg.prototype.getKey=function(){return hd(this,1)};
Fg.prototype.getValue=function(){return hd(this,2===kd(this,Gg)?2:-1)};
Fg.prototype.setValue=function(a){return jd(this,2,Gg,a)};
var Gg=[2,3,4,5,6];function Hg(a){J.call(this,a)}
r(Hg,J);function Ig(a){J.call(this,a)}
r(Ig,J);function Jg(a){J.call(this,a)}
r(Jg,J);function Kg(a){J.call(this,a,-1,Lg)}
r(Kg,J);Kg.prototype.getPlayerType=function(){return hd(this,36)};
Kg.prototype.setHomeGroupInfo=function(a){return H(this,81,a)};
var Lg=[9,66,24,32,86,100,101];function Mg(a){J.call(this,a,-1,Ng)}
r(Mg,J);var Ng=[15,26,28];function Og(a){J.call(this,a)}
r(Og,J);Og.prototype.setToken=function(a){return D(this,2,a)};function Pg(a){J.call(this,a,-1,Qg)}
r(Pg,J);Pg.prototype.setSafetyMode=function(a){return D(this,5,a)};
var Qg=[12];function Rg(a){J.call(this,a,-1,Sg)}
r(Rg,J);var Sg=[12];function Tg(a){J.call(this,a,-1,Ug)}
r(Tg,J);function Vg(a){J.call(this,a)}
r(Vg,J);Vg.prototype.getKey=function(){return pd(this,1)};
Vg.prototype.getValue=function(){return pd(this,2)};
Vg.prototype.setValue=function(a){return D(this,2,a)};
var Ug=[4,5];function Wg(a){J.call(this,a)}
r(Wg,J);function Xg(a){J.call(this,a)}
r(Xg,J);var Yg=[2,3];function Zg(a){J.call(this,a)}
r(Zg,J);Zg.prototype.getMessage=function(){return pd(this,1)};function $g(a){J.call(this,a)}
r($g,J);function ah(a){J.call(this,a)}
r(ah,J);function bh(a){J.call(this,a,-1,ch)}
r(bh,J);var ch=[10,17];function dh(a){J.call(this,a)}
r(dh,J);function eh(a){J.call(this,a)}
r(eh,J);eh.prototype.S=function(a){D(this,1,a)};function fh(a){J.call(this,a)}
r(fh,J);function gh(a){J.call(this,a)}
r(gh,J);function hh(a){J.call(this,a)}
r(hh,J);function ih(a,b){H(a,1,b)}
hh.prototype.S=function(a){D(this,2,a)};
function jh(a){J.call(this,a)}
r(jh,J);function kh(a,b){H(a,1,b)}
;function lh(a){J.call(this,a,-1,mh)}
r(lh,J);lh.prototype.S=function(a){D(this,1,a)};
function nh(a,b){H(a,2,b)}
var mh=[3];function oh(a){J.call(this,a)}
r(oh,J);oh.prototype.S=function(a){D(this,1,a)};function ph(a){J.call(this,a)}
r(ph,J);ph.prototype.S=function(a){D(this,1,a)};function qh(a){J.call(this,a)}
r(qh,J);qh.prototype.S=function(a){D(this,1,a)};function rh(a){J.call(this,a)}
r(rh,J);function sh(a){J.call(this,a)}
r(sh,J);function th(a){J.call(this,a,-1,uh)}
r(th,J);th.prototype.getPlayerType=function(){var a=hd(this,7);return null==a?0:a};
th.prototype.setVideoId=function(a){return D(this,19,a)};
function vh(a,b){od(a,68,wh,b)}
function wh(a){J.call(this,a)}
r(wh,J);wh.prototype.getId=function(){return pd(this,2)};
var uh=[83,68];function xh(a){J.call(this,a)}
r(xh,J);function yh(a){J.call(this,a)}
r(yh,J);function zh(a){J.call(this,a)}
r(zh,J);function Ah(a){J.call(this,a,428)}
r(Ah,J);
var Bh=[23,24,11,6,7,5,2,3,20,21,28,32,37,229,241,45,59,225,288,72,73,78,208,156,202,215,74,76,79,80,111,85,91,97,100,102,105,119,126,127,136,146,157,158,159,163,164,168,176,222,383,177,178,179,411,184,188,189,190,191,193,194,195,196,198,199,200,201,203,204,205,206,258,259,260,261,209,226,227,232,233,234,240,247,248,251,254,255,270,278,291,293,300,304,308,309,310,311,313,314,319,321,323,324,328,330,331,332,337,338,340,344,348,350,351,352,353,354,355,356,357,358,361,363,364,368,369,370,373,374,375,
378,380,381,388,389,403,412,413,414,415,416,417,418,419,420,423,424,425,426,427,117];var Ch={Fh:0,qh:1,wh:2,xh:4,Ch:8,yh:16,zh:32,Eh:64,Dh:128,sh:256,uh:512,Bh:1024,th:2048,vh:4096,rh:8192,Ah:16384};function Dh(a){J.call(this,a)}
r(Dh,J);function Eh(a){J.call(this,a)}
r(Eh,J);Eh.prototype.setVideoId=function(a){return jd(this,1,Fh,a)};
Eh.prototype.getPlaylistId=function(){return hd(this,2===kd(this,Fh)?2:-1)};
var Fh=[1,2];function Gh(a){J.call(this,a,-1,Hh)}
r(Gh,J);var Hh=[3];function Ih(a){J.call(this,a,1)}
r(Ih,J);function Jh(a){J.call(this,a)}
r(Jh,J);var Kh;Kh=new function(a,b){this.h=a;this.fieldName=b;this.isRepeated=0;this.i=xd}(406606992,{Qo:0},Jh);function Lh(){Jh.apply(this,arguments)}
r(Lh,Jh);oe(Lh);function Mh(a,b){1<b.length?a[b[0]]=b[1]:1===b.length&&Object.assign(a,b[0])}
;var Nh=x.window,Oh,Ph,Qh=(null==Nh?void 0:null==(Oh=Nh.yt)?void 0:Oh.config_)||(null==Nh?void 0:null==(Ph=Nh.ytcfg)?void 0:Ph.data_)||{},Rh,Sh=(null==Nh?void 0:null==(Rh=Nh.ytcfg)?void 0:Rh.obfuscatedData_)||[];function Th(){Ih.apply(this,arguments)}
r(Th,Ih);oe(Th);var Uh=new Th(Sh),Vh=Qh.EXPERIMENT_FLAGS;if(!Vh||!Vh.jspb_i18n_extension){var Wh=new Lh;Kh.i(Uh,Wh)}y("yt.config_",Qh);y("yt.configJspb_",Sh);function Xh(){Mh(Qh,arguments)}
function A(a,b){return a in Qh?Qh[a]:b}
function Yh(){var a=Qh.EXPERIMENT_FLAGS;return a?a.web_disable_gel_stp_ecatcher_killswitch:void 0}
;function M(a){a=Zh(a);return"string"===typeof a&&"false"===a?!1:!!a}
function $h(a,b){a=Zh(a);return void 0===a&&void 0!==b?b:Number(a||0)}
function ai(){return A("EXPERIMENTS_TOKEN","")}
function Zh(a){var b=A("EXPERIMENTS_FORCED_FLAGS",{});return void 0!==b[a]?b[a]:A("EXPERIMENT_FLAGS",{})[a]}
function bi(){var a=[],b=A("EXPERIMENTS_FORCED_FLAGS",{});for(c in b)a.push({key:c,value:String(b[c])});var c=A("EXPERIMENT_FLAGS",{});for(var d in c)d.startsWith("force_")&&void 0===b[d]&&a.push({key:d,value:String(c[d])});return a}
;var ci=[];function di(a){ci.forEach(function(b){return b(a)})}
function ei(a){return a&&window.yterr?function(){try{return a.apply(this,arguments)}catch(b){fi(b)}}:a}
function fi(a,b,c,d){var e=z("yt.logging.errors.log");e?e(a,"ERROR",b,c,d):(e=A("ERRORS",[]),e.push([a,"ERROR",b,c,d]),Xh("ERRORS",e));di(a)}
function gi(a,b,c,d){var e=z("yt.logging.errors.log");e?e(a,"WARNING",b,c,d):(e=A("ERRORS",[]),e.push([a,"WARNING",b,c,d]),Xh("ERRORS",e))}
;function hi(){var a=ii;z("yt.ads.biscotti.getId_")||y("yt.ads.biscotti.getId_",a)}
function ji(a){y("yt.ads.biscotti.lastId_",a)}
;var ki=/^[\w.]*$/,li={q:!0,search_query:!0};function mi(a,b){b=a.split(b);for(var c={},d=0,e=b.length;d<e;d++){var f=b[d].split("=");if(1==f.length&&f[0]||2==f.length)try{var g=ni(f[0]||""),h=ni(f[1]||"");g in c?Array.isArray(c[g])?lb(c[g],h):c[g]=[c[g],h]:c[g]=h}catch(u){var k=u,m=f[0],q=String(mi);k.args=[{key:m,value:f[1],query:a,method:oi==q?"unchanged":q}];li.hasOwnProperty(m)||gi(k)}}return c}
var oi=String(mi);function pi(a){var b=[];mb(a,function(c,d){var e=encodeURIComponent(String(d)),f;Array.isArray(c)?f=c:f=[c];fb(f,function(g){""==g?b.push(e):b.push(e+"="+encodeURIComponent(String(g)))})});
return b.join("&")}
function qi(a){"?"==a.charAt(0)&&(a=a.substr(1));return mi(a,"&")}
function ri(a){return-1!=a.indexOf("?")?(a=(a||"").split("#")[0],a=a.split("?",2),qi(1<a.length?a[1]:a[0])):{}}
function si(a,b,c){var d=a.split("#",2);a=d[0];d=1<d.length?"#"+d[1]:"";var e=a.split("?",2);a=e[0];e=qi(e[1]||"");for(var f in b)!c&&null!==e&&f in e||(e[f]=b[f]);return hc(a,e)+d}
function ti(a){if(!b)var b=window.location.href;var c=cc(1,a),d=dc(a);c&&d?(a=a.match(ac),b=b.match(ac),a=a[3]==b[3]&&a[1]==b[1]&&a[4]==b[4]):a=d?dc(b)==d&&(Number(cc(4,b))||null)==(Number(cc(4,a))||null):!0;return a}
function ni(a){return a&&a.match(ki)?a:decodeURIComponent(a.replace(/\+/g," "))}
;function ui(a){var b=vi;a=void 0===a?z("yt.ads.biscotti.lastId_")||"":a;var c=Object,d=c.assign,e={};e.dt=$d;e.flash="0";a:{try{var f=b.h.top.location.href}catch(ua){f=2;break a}f=f?f===b.i.location.href?0:1:2}e=(e.frm=f,e);try{e.u_tz=-(new Date).getTimezoneOffset();var g=void 0===g?Bd:g;try{var h=g.history.length}catch(ua){h=0}e.u_his=h;var k;e.u_h=null==(k=Bd.screen)?void 0:k.height;var m;e.u_w=null==(m=Bd.screen)?void 0:m.width;var q;e.u_ah=null==(q=Bd.screen)?void 0:q.availHeight;var u;e.u_aw=
null==(u=Bd.screen)?void 0:u.availWidth;var C;e.u_cd=null==(C=Bd.screen)?void 0:C.colorDepth}catch(ua){}h=b.h;try{var v=h.screenX;var E=h.screenY}catch(ua){}try{var F=h.outerWidth;var I=h.outerHeight}catch(ua){}try{var R=h.innerWidth;var O=h.innerHeight}catch(ua){}try{var S=h.screenLeft;var ka=h.screenTop}catch(ua){}try{R=h.innerWidth,O=h.innerHeight}catch(ua){}try{var N=h.screen.availWidth;var Ca=h.screen.availTop}catch(ua){}v=[S,ka,v,E,N,Ca,F,I,R,O];try{var Oa=(b.h.top||window).document,va="CSS1Compat"==
Oa.compatMode?Oa.documentElement:Oa.body;var G=(new Jd(va.clientWidth,va.clientHeight)).round()}catch(ua){G=new Jd(-12245933,-12245933)}Oa=G;G={};var Da=void 0===Da?x:Da;va=new df;Da.SVGElement&&Da.document.createElementNS&&va.set(0);E=Rd();E["allow-top-navigation-by-user-activation"]&&va.set(1);E["allow-popups-to-escape-sandbox"]&&va.set(2);Da.crypto&&Da.crypto.subtle&&va.set(3);Da.TextDecoder&&Da.TextEncoder&&va.set(4);Da=ef(va);G.bc=Da;G.bih=Oa.height;G.biw=Oa.width;G.brdim=v.join();b=b.i;b=(G.vis=
b.prerendering?3:{visible:1,hidden:2,prerender:3,preview:4,unloaded:5}[b.visibilityState||b.webkitVisibilityState||b.mozVisibilityState||""]||0,G.wgl=!!Bd.WebGLRenderingContext,G);c=d.call(c,e,b);c.ca_type="image";a&&(c.bid=a);return c}
var vi=new function(){var a=window.document;this.h=window;this.i=a};
y("yt.ads_.signals_.getAdSignalsString",function(a){return pi(ui(a))});Date.now();var wi="XMLHttpRequest"in x?function(){return new XMLHttpRequest}:null;
function xi(){if(!wi)return null;var a=wi();return"open"in a?a:null}
function yi(a){switch(a&&"status"in a?a.status:-1){case 200:case 201:case 202:case 203:case 204:case 205:case 206:case 304:return!0;default:return!1}}
;function zi(a,b){"function"===typeof a&&(a=ei(a));return window.setTimeout(a,b)}
function Ai(a){window.clearTimeout(a)}
;var Bi={Authorization:"AUTHORIZATION","X-Goog-EOM-Visitor-Id":"EOM_VISITOR_DATA","X-Goog-Visitor-Id":"SANDBOXED_VISITOR_ID","X-Youtube-Domain-Admin-State":"DOMAIN_ADMIN_STATE","X-Youtube-Chrome-Connected":"CHROME_CONNECTED_HEADER","X-YouTube-Client-Name":"INNERTUBE_CONTEXT_CLIENT_NAME","X-YouTube-Client-Version":"INNERTUBE_CONTEXT_CLIENT_VERSION","X-YouTube-Delegation-Context":"INNERTUBE_CONTEXT_SERIALIZED_DELEGATION_CONTEXT","X-YouTube-Device":"DEVICE","X-Youtube-Identity-Token":"ID_TOKEN","X-YouTube-Page-CL":"PAGE_CL",
"X-YouTube-Page-Label":"PAGE_BUILD_LABEL","X-YouTube-Variants-Checksum":"VARIANTS_CHECKSUM"},Ci="app debugcss debugjs expflag force_ad_params force_ad_encrypted force_viral_ad_response_params forced_experiments innertube_snapshots innertube_goldens internalcountrycode internalipoverride absolute_experiments conditional_experiments sbb sr_bns_address".split(" ").concat(fa(be)),Yi=!1;
function Zi(a,b){b=void 0===b?{}:b;var c=ti(a),d=M("web_ajax_ignore_global_headers_if_set"),e;for(e in Bi){var f=A(Bi[e]);!f||!c&&dc(a)||d&&void 0!==b[e]||!M("enable_web_eom_visitor_data")&&"X-Goog-EOM-Visitor-Id"===e||(b[e]=f)}"X-Goog-EOM-Visitor-Id"in b&&"X-Goog-Visitor-Id"in b&&delete b["X-Goog-Visitor-Id"];if(c||!dc(a))b["X-YouTube-Utc-Offset"]=String(-(new Date).getTimezoneOffset());if(c||!dc(a)){try{var g=(new Intl.DateTimeFormat).resolvedOptions().timeZone}catch(h){}g&&(b["X-YouTube-Time-Zone"]=
g)}if(c||!dc(a))b["X-YouTube-Ad-Signals"]=pi(ui());return b}
function $i(a){var b=window.location.search,c=dc(a);M("debug_handle_relative_url_for_query_forward_killswitch")||c||!ti(a)||(c=document.location.hostname);var d=bc(cc(5,a));d=(c=c&&(c.endsWith("youtube.com")||c.endsWith("youtube-nocookie.com")))&&d&&d.startsWith("/api/");if(!c||d)return a;var e=qi(b),f={};fb(Ci,function(g){e[g]&&(f[g]=e[g])});
return si(a,f||{},!1)}
function aj(a,b){var c=b.format||"JSON";a=bj(a,b);var d=cj(a,b),e=!1,f=dj(a,function(k){if(!e){e=!0;h&&Ai(h);var m=yi(k),q=null,u=400<=k.status&&500>k.status,C=500<=k.status&&600>k.status;if(m||u||C)q=ej(a,c,k,b.convertToSafeHtml);if(m)a:if(k&&204==k.status)m=!0;else{switch(c){case "XML":m=0==parseInt(q&&q.return_code,10);break a;case "RAW":m=!0;break a}m=!!q}q=q||{};u=b.context||x;m?b.onSuccess&&b.onSuccess.call(u,k,q):b.onError&&b.onError.call(u,k,q);b.onFinish&&b.onFinish.call(u,k,q)}},b.method,
d,b.headers,b.responseType,b.withCredentials);
d=b.timeout||0;if(b.onTimeout&&0<d){var g=b.onTimeout;var h=zi(function(){e||(e=!0,f.abort(),Ai(h),g.call(b.context||x,f))},d)}return f}
function bj(a,b){b.includeDomain&&(a=document.location.protocol+"//"+document.location.hostname+(document.location.port?":"+document.location.port:"")+a);var c=A("XSRF_FIELD_NAME");if(b=b.urlParams)b[c]&&delete b[c],a=si(a,b||{},!0);return a}
function cj(a,b){var c=A("XSRF_FIELD_NAME"),d=A("XSRF_TOKEN"),e=b.postBody||"",f=b.postParams,g=A("XSRF_FIELD_NAME"),h;b.headers&&(h=b.headers["Content-Type"]);b.excludeXsrf||dc(a)&&!b.withCredentials&&dc(a)!=document.location.hostname||"POST"!=b.method||h&&"application/x-www-form-urlencoded"!=h||b.postParams&&b.postParams[g]||(f||(f={}),f[c]=d);f&&"string"===typeof e&&(e=qi(e),yb(e,f),e=b.postBodyFormat&&"JSON"==b.postBodyFormat?JSON.stringify(e):gc(e));f=e||f&&!pb(f);!Yi&&f&&"POST"!=b.method&&(Yi=
!0,fi(Error("AJAX request with postData should use POST")));return e}
function ej(a,b,c,d){var e=null;switch(b){case "JSON":try{var f=c.responseText}catch(g){throw d=Error("Error reading responseText"),d.params=a,gi(d),g;}a=c.getResponseHeader("Content-Type")||"";f&&0<=a.indexOf("json")&&(")]}'\n"===f.substring(0,5)&&(f=f.substring(5)),e=JSON.parse(f));break;case "XML":if(a=(a=c.responseXML)?fj(a):null)e={},fb(a.getElementsByTagName("*"),function(g){e[g.tagName]=gj(g)})}d&&hj(e);
return e}
function hj(a){if(Ra(a))for(var b in a){var c;(c="html_content"==b)||(c=b.length-5,c=0<=c&&b.indexOf("_html",c)==c);if(c){c=b;Db("HTML that is escaped and sanitized server-side and passed through yt.net.ajax");var d=a[b],e=Ab();d=e?e.createHTML(d):d;a[c]=new Ub(d)}else hj(a[b])}}
function fj(a){return a?(a=("responseXML"in a?a.responseXML:a).getElementsByTagName("root"))&&0<a.length?a[0]:null:null}
function gj(a){var b="";fb(a.childNodes,function(c){b+=c.nodeValue});
return b}
function dj(a,b,c,d,e,f,g){function h(){4==(k&&"readyState"in k?k.readyState:0)&&b&&ei(b)(k)}
c=void 0===c?"GET":c;d=void 0===d?"":d;var k=xi();if(!k)return null;"onloadend"in k?k.addEventListener("loadend",h,!1):k.onreadystatechange=h;M("debug_forward_web_query_parameters")&&(a=$i(a));k.open(c,a,!0);f&&(k.responseType=f);g&&(k.withCredentials=!0);c="POST"==c&&(void 0===window.FormData||!(d instanceof FormData));if(e=Zi(a,e))for(var m in e)k.setRequestHeader(m,e[m]),"content-type"==m.toLowerCase()&&(c=!1);c&&k.setRequestHeader("Content-Type","application/x-www-form-urlencoded");k.send(d);
return k}
;function ij(a){var b=this;this.h=void 0;a.addEventListener("beforeinstallprompt",function(c){c.preventDefault();b.h=c})}
function jj(){if(!x.matchMedia)return"WEB_DISPLAY_MODE_UNKNOWN";try{return x.matchMedia("(display-mode: standalone)").matches?"WEB_DISPLAY_MODE_STANDALONE":x.matchMedia("(display-mode: minimal-ui)").matches?"WEB_DISPLAY_MODE_MINIMAL_UI":x.matchMedia("(display-mode: fullscreen)").matches?"WEB_DISPLAY_MODE_FULLSCREEN":x.matchMedia("(display-mode: browser)").matches?"WEB_DISPLAY_MODE_BROWSER":"WEB_DISPLAY_MODE_UNKNOWN"}catch(a){return"WEB_DISPLAY_MODE_UNKNOWN"}}
function kj(){var a=jj();a=Object.keys(cf).indexOf(a);return-1===a?null:a}
;function lj(a,b,c,d,e){je.set(""+a,b,{Oa:c,path:"/",domain:void 0===d?"youtube.com":d,secure:void 0===e?!1:e})}
function mj(a){return je.get(""+a,void 0)}
function nj(){if(!je.isEnabled())return!1;if(!je.isEmpty())return!0;je.set("TESTCOOKIESENABLED","1",{Oa:60});if("1"!==je.get("TESTCOOKIESENABLED"))return!1;je.remove("TESTCOOKIESENABLED");return!0}
;var oj=z("ytglobal.prefsUserPrefsPrefs_")||{};y("ytglobal.prefsUserPrefsPrefs_",oj);function pj(){this.h=A("ALT_PREF_COOKIE_NAME","PREF");this.i=A("ALT_PREF_COOKIE_DOMAIN","youtube.com");var a=mj(this.h);if(a){a=decodeURIComponent(a).split("&");for(var b=0;b<a.length;b++){var c=a[b].split("="),d=c[0];(c=c[1])&&(oj[d]=c.toString())}}}
pj.prototype.get=function(a,b){qj(a);rj(a);a=void 0!==oj[a]?oj[a].toString():null;return null!=a?a:b?b:""};
pj.prototype.set=function(a,b){qj(a);rj(a);if(null==b)throw Error("ExpectedNotNull");oj[a]=b.toString()};
function sj(a){return!!((tj("f"+(Math.floor(a/31)+1))||0)&1<<a%31)}
pj.prototype.remove=function(a){qj(a);rj(a);delete oj[a]};
pj.prototype.clear=function(){for(var a in oj)delete oj[a]};
function rj(a){if(/^f([1-9][0-9]*)$/.test(a))throw Error("ExpectedRegexMatch: "+a);}
function qj(a){if(!/^\w+$/.test(a))throw Error("ExpectedRegexMismatch: "+a);}
function tj(a){a=void 0!==oj[a]?oj[a].toString():null;return null!=a&&/^[A-Fa-f0-9]+$/.test(a)?parseInt(a,16):null}
Na(pj);var uj={bluetooth:"CONN_DISCO",cellular:"CONN_CELLULAR_UNKNOWN",ethernet:"CONN_WIFI",none:"CONN_NONE",wifi:"CONN_WIFI",wimax:"CONN_CELLULAR_4G",other:"CONN_UNKNOWN",unknown:"CONN_UNKNOWN","slow-2g":"CONN_CELLULAR_2G","2g":"CONN_CELLULAR_2G","3g":"CONN_CELLULAR_3G","4g":"CONN_CELLULAR_4G"},vj={CONN_DEFAULT:0,CONN_UNKNOWN:1,CONN_NONE:2,CONN_WIFI:3,CONN_CELLULAR_2G:4,CONN_CELLULAR_3G:5,CONN_CELLULAR_4G:6,CONN_CELLULAR_UNKNOWN:7,CONN_DISCO:8,CONN_CELLULAR_5G:9,CONN_WIFI_METERED:10,CONN_CELLULAR_5G_SA:11,
CONN_CELLULAR_5G_NSA:12,CONN_INVALID:31},wj={EFFECTIVE_CONNECTION_TYPE_UNKNOWN:0,EFFECTIVE_CONNECTION_TYPE_OFFLINE:1,EFFECTIVE_CONNECTION_TYPE_SLOW_2G:2,EFFECTIVE_CONNECTION_TYPE_2G:3,EFFECTIVE_CONNECTION_TYPE_3G:4,EFFECTIVE_CONNECTION_TYPE_4G:5},xj={"slow-2g":"EFFECTIVE_CONNECTION_TYPE_SLOW_2G","2g":"EFFECTIVE_CONNECTION_TYPE_2G","3g":"EFFECTIVE_CONNECTION_TYPE_3G","4g":"EFFECTIVE_CONNECTION_TYPE_4G"};function yj(){var a=x.navigator;return a?a.connection:void 0}
function zj(){var a=yj();if(a){var b=uj[a.type||"unknown"]||"CONN_UNKNOWN";a=uj[a.effectiveType||"unknown"]||"CONN_UNKNOWN";"CONN_CELLULAR_UNKNOWN"===b&&"CONN_UNKNOWN"!==a&&(b=a);if("CONN_UNKNOWN"!==b)return b;if("CONN_UNKNOWN"!==a)return a}}
function Aj(){var a=yj();if(null!=a&&a.effectiveType)return xj.hasOwnProperty(a.effectiveType)?xj[a.effectiveType]:"EFFECTIVE_CONNECTION_TYPE_UNKNOWN"}
;function Bj(){return"INNERTUBE_API_KEY"in Qh&&"INNERTUBE_API_VERSION"in Qh}
function Cj(){return{innertubeApiKey:A("INNERTUBE_API_KEY"),innertubeApiVersion:A("INNERTUBE_API_VERSION"),ab:A("INNERTUBE_CONTEXT_CLIENT_CONFIG_INFO"),bb:A("INNERTUBE_CONTEXT_CLIENT_NAME","WEB"),Vb:A("INNERTUBE_CONTEXT_CLIENT_NAME",1),innertubeContextClientVersion:A("INNERTUBE_CONTEXT_CLIENT_VERSION"),xb:A("INNERTUBE_CONTEXT_HL"),wb:A("INNERTUBE_CONTEXT_GL"),Wb:A("INNERTUBE_HOST_OVERRIDE")||"",Yb:!!A("INNERTUBE_USE_THIRD_PARTY_AUTH",!1),Xb:!!A("INNERTUBE_OMIT_API_KEY_WHEN_AUTH_HEADER_IS_PRESENT",
!1),appInstallData:A("SERIALIZED_CLIENT_CONFIG_DATA")}}
function Dj(a){var b={client:{hl:a.xb,gl:a.wb,clientName:a.bb,clientVersion:a.innertubeContextClientVersion,configInfo:a.ab}};navigator.userAgent&&(b.client.userAgent=String(navigator.userAgent));var c=x.devicePixelRatio;c&&1!=c&&(b.client.screenDensityFloat=String(c));c=ai();""!==c&&(b.client.experimentsToken=c);c=bi();0<c.length&&(b.request={internalExperimentFlags:c});Ej(a,void 0,b);Fj(void 0,b);Gj(a,void 0,b);Hj(void 0,b);A("DELEGATED_SESSION_ID")&&!M("pageid_as_header_web")&&(b.user={onBehalfOfUser:A("DELEGATED_SESSION_ID")});
a=Object;c=a.assign;for(var d=b.client,e={},f=p(Object.entries(qi(A("DEVICE","")))),g=f.next();!g.done;g=f.next()){var h=p(g.value);g=h.next().value;h=h.next().value;"cbrand"===g?e.deviceMake=h:"cmodel"===g?e.deviceModel=h:"cbr"===g?e.browserName=h:"cbrver"===g?e.browserVersion=h:"cos"===g?e.osName=h:"cosver"===g?e.osVersion=h:"cplatform"===g&&(e.platform=h)}b.client=c.call(a,d,e);return b}
function Ij(a){var b=new Rg,c=new Kg;D(c,1,a.xb);D(c,2,a.wb);D(c,16,a.Vb);D(c,17,a.innertubeContextClientVersion);if(a.ab){var d=a.ab,e=new Hg;d.coldConfigData&&D(e,1,d.coldConfigData);d.appInstallData&&D(e,6,d.appInstallData);d.coldHashData&&D(e,3,d.coldHashData);d.hotHashData&&D(e,5,d.hotHashData);H(c,62,e)}(d=x.devicePixelRatio)&&1!=d&&D(c,65,d);d=ai();""!==d&&D(c,54,d);d=bi();if(0<d.length){e=new Mg;for(var f=0;f<d.length;f++){var g=new Fg;D(g,1,d[f].key);g.setValue(d[f].value);od(e,15,Fg,g)}H(b,
5,e)}Ej(a,c);d=a.bb;if(("WEB_REMIX"===d||76===d)&&!M("music_web_display_mode_killswitch")&&c){var h;d=null!=(h=ld(c,Jg,70))?h:new Jg;h=kj();null!==h&&D(d,10,h);H(c,70,d)}Fj(c);Gj(a,c);Hj(c);A("DELEGATED_SESSION_ID")&&!M("pageid_as_header_web")&&(a=new Pg,D(a,3,A("DELEGATED_SESSION_ID")));a=p(Object.entries(qi(A("DEVICE",""))));for(h=a.next();!h.done;h=a.next())d=p(h.value),h=d.next().value,d=d.next().value,"cbrand"===h?D(c,12,d):"cmodel"===h?D(c,13,d):"cbr"===h?D(c,87,d):"cbrver"===h?D(c,88,d):"cos"===
h?D(c,18,d):"cosver"===h?D(c,19,d):"cplatform"===h&&D(c,42,d);H(b,1,c);return b}
function Ej(a,b,c){a=a.bb;if("WEB"===a||"MWEB"===a||1===a||2===a)if(b){c=ld(b,Ig,96)||new Ig;var d=kj();null!==d&&D(c,3,d);H(b,96,c)}else c&&(c.client.mainAppWebInfo=null!=(d=c.client.mainAppWebInfo)?d:{},c.client.mainAppWebInfo.webDisplayMode=jj())}
function Fj(a,b){var c;if(M("web_log_memory_total_kbytes")&&(null==(c=x.navigator)?0:c.deviceMemory)){var d;c=null==(d=x.navigator)?void 0:d.deviceMemory;a?D(a,95,1E6*c):b&&(b.client.memoryTotalKbytes=""+1E6*c)}}
function Gj(a,b,c){if(a.appInstallData)if(b){var d;c=null!=(d=ld(b,Hg,62))?d:new Hg;D(c,6,a.appInstallData);H(b,62,c)}else c&&(c.client.configInfo=c.client.configInfo||{},c.client.configInfo.appInstallData=a.appInstallData)}
function Hj(a,b){var c=zj();c&&(a?D(a,61,vj[c]):b&&(b.client.connectionType=c));M("web_log_effective_connection_type")&&(c=Aj())&&(a?D(a,94,wj[c]):b&&(b.client.effectiveConnectionType=c))}
function Jj(a,b,c){c=void 0===c?{}:c;var d={};M("enable_web_eom_visitor_data")&&A("EOM_VISITOR_DATA")?d={"X-Goog-EOM-Visitor-Id":A("EOM_VISITOR_DATA")}:d={"X-Goog-Visitor-Id":c.visitorData||A("VISITOR_DATA","")};if(b&&b.includes("www.youtube-nocookie.com"))return d;(b=c.Lo||A("AUTHORIZATION"))||(a?b="Bearer "+z("gapi.auth.getToken")().Ko:b=ne([]));b&&(d.Authorization=b,d["X-Goog-AuthUser"]=A("SESSION_INDEX",0),M("pageid_as_header_web")&&(d["X-Goog-PageId"]=A("DELEGATED_SESSION_ID")));return d}
;function Kj(a){a=Object.assign({},a);delete a.Authorization;var b=ne();if(b){var c=new xf;c.update(A("INNERTUBE_API_KEY"));c.update(b);a.hash=Lc(c.digest(),3)}return a}
;function Lj(a){var b=new yg;(b=b.isAvailable()?a?new Eg(b,a):b:null)||(a=new zg(a||"UserDataSharedStore"),b=a.isAvailable()?a:null);this.h=(a=b)?new ug(a):null;this.i=document.domain||window.location.hostname}
Lj.prototype.set=function(a,b,c,d){c=c||31104E3;this.remove(a);if(this.h)try{this.h.set(a,b,Date.now()+1E3*c);return}catch(f){}var e="";if(d)try{e=escape(Qf(b))}catch(f){return}else e=escape(b);lj(a,e,c,this.i)};
Lj.prototype.get=function(a,b){var c=void 0,d=!this.h;if(!d)try{c=this.h.get(a)}catch(e){d=!0}if(d&&(c=mj(a))&&(c=unescape(c),b))try{c=JSON.parse(c)}catch(e){this.remove(a),c=void 0}return c};
Lj.prototype.remove=function(a){this.h&&this.h.remove(a);var b=this.i;je.remove(""+a,"/",void 0===b?"youtube.com":b)};var Mj=window,P=Mj.ytcsi&&Mj.ytcsi.now?Mj.ytcsi.now:Mj.performance&&Mj.performance.timing&&Mj.performance.now&&Mj.performance.timing.navigationStart?function(){return Mj.performance.timing.navigationStart+Mj.performance.now()}:function(){return(new Date).getTime()};var Nj;function Oj(){Nj||(Nj=new Lj("yt.innertube"));return Nj}
function Pj(a,b,c,d){if(d)return null;d=Oj().get("nextId",!0)||1;var e=Oj().get("requests",!0)||{};e[d]={method:a,request:b,authState:Kj(c),requestTime:Math.round(P())};Oj().set("nextId",d+1,86400,!0);Oj().set("requests",e,86400,!0);return d}
function Qj(a){var b=Oj().get("requests",!0)||{};delete b[a];Oj().set("requests",b,86400,!0)}
function Rj(a){var b=Oj().get("requests",!0);if(b){for(var c in b){var d=b[c];if(!(6E4>Math.round(P())-d.requestTime)){var e=d.authState,f=Kj(Jj(!1));ub(e,f)&&(e=d.request,"requestTimeMs"in e&&(e.requestTimeMs=Math.round(P())),Sj(a,d.method,e,{}));delete b[c]}}Oj().set("requests",b,86400,!0)}}
;function Tj(){}
function Uj(a,b){return Vj(a,0,b)}
Tj.prototype.N=function(a,b){return Vj(a,1,b)};
function Wj(a,b){Vj(a,2,b)}
function Xj(a){var b=z("yt.scheduler.instance.addImmediateJob");b?b(a):a()}
;function Yj(){Tj.apply(this,arguments)}
r(Yj,Tj);function Zj(){Yj.h||(Yj.h=new Yj);return Yj.h}
function Vj(a,b,c){void 0!==c&&Number.isNaN(Number(c))&&(c=void 0);var d=z("yt.scheduler.instance.addJob");return d?d(a,b,c):void 0===c?(a(),NaN):zi(a,c||0)}
Yj.prototype.U=function(a){if(void 0===a||!Number.isNaN(Number(a))){var b=z("yt.scheduler.instance.cancelJob");b?b(a):Ai(a)}};
Yj.prototype.start=function(){var a=z("yt.scheduler.instance.start");a&&a()};
Yj.prototype.pause=function(){var a=z("yt.scheduler.instance.pause");a&&a()};var bf=Zj();var ak=Gc||Hc;function bk(a){var b=Rb();return b?0<=b.toLowerCase().indexOf(a):!1}
;var ck=function(){var a;return function(){a||(a=new Lj("ytidb"));return a}}();
function dk(){var a;return null==(a=ck())?void 0:a.get("LAST_RESULT_ENTRY_KEY",!0)}
;var ek=[],fk,gk=!1;function hk(){var a={};for(fk=new ik(void 0===a.handleError?jk:a.handleError,void 0===a.logEvent?kk:a.logEvent);0<ek.length;)switch(a=ek.shift(),a.type){case "ERROR":fk.handleError(a.payload);break;case "EVENT":fk.logEvent(a.eventType,a.payload)}}
function lk(a){gk||(fk?fk.handleError(a):(ek.push({type:"ERROR",payload:a}),10<ek.length&&ek.shift()))}
function mk(a,b){gk||(fk?fk.logEvent(a,b):(ek.push({type:"EVENT",eventType:a,payload:b}),10<ek.length&&ek.shift()))}
;function Q(a){var b=Ja.apply(1,arguments);var c=Error.call(this,a);this.message=c.message;"stack"in c&&(this.stack=c.stack);this.args=[].concat(fa(b))}
r(Q,Error);function nk(){try{return ok(),!0}catch(a){return!1}}
function ok(a){if(void 0!==A("DATASYNC_ID"))return A("DATASYNC_ID");throw new Q("Datasync ID not set",void 0===a?"unknown":a);}
;function pk(a){if(0<=a.indexOf(":"))throw Error("Database name cannot contain ':'");}
function qk(a){return a.substr(0,a.indexOf(":"))||a}
;var rk={},sk=(rk.AUTH_INVALID="No user identifier specified.",rk.EXPLICIT_ABORT="Transaction was explicitly aborted.",rk.IDB_NOT_SUPPORTED="IndexedDB is not supported.",rk.MISSING_INDEX="Index not created.",rk.MISSING_OBJECT_STORES="Object stores not created.",rk.DB_DELETED_BY_MISSING_OBJECT_STORES="Database is deleted because expected object stores were not created.",rk.DB_REOPENED_BY_MISSING_OBJECT_STORES="Database is reopened because expected object stores were not created.",rk.UNKNOWN_ABORT="Transaction was aborted for unknown reasons.",
rk.QUOTA_EXCEEDED="The current transaction exceeded its quota limitations.",rk.QUOTA_MAYBE_EXCEEDED="The current transaction may have failed because of exceeding quota limitations.",rk.EXECUTE_TRANSACTION_ON_CLOSED_DB="Can't start a transaction on a closed database",rk.INCOMPATIBLE_DB_VERSION="The binary is incompatible with the database version",rk),tk={},uk=(tk.AUTH_INVALID="ERROR",tk.EXECUTE_TRANSACTION_ON_CLOSED_DB="WARNING",tk.EXPLICIT_ABORT="IGNORED",tk.IDB_NOT_SUPPORTED="ERROR",tk.MISSING_INDEX=
"WARNING",tk.MISSING_OBJECT_STORES="ERROR",tk.DB_DELETED_BY_MISSING_OBJECT_STORES="WARNING",tk.DB_REOPENED_BY_MISSING_OBJECT_STORES="WARNING",tk.QUOTA_EXCEEDED="WARNING",tk.QUOTA_MAYBE_EXCEEDED="WARNING",tk.UNKNOWN_ABORT="WARNING",tk.INCOMPATIBLE_DB_VERSION="WARNING",tk),vk={},wk=(vk.AUTH_INVALID=!1,vk.EXECUTE_TRANSACTION_ON_CLOSED_DB=!1,vk.EXPLICIT_ABORT=!1,vk.IDB_NOT_SUPPORTED=!1,vk.MISSING_INDEX=!1,vk.MISSING_OBJECT_STORES=!1,vk.DB_DELETED_BY_MISSING_OBJECT_STORES=!1,vk.DB_REOPENED_BY_MISSING_OBJECT_STORES=
!1,vk.QUOTA_EXCEEDED=!1,vk.QUOTA_MAYBE_EXCEEDED=!0,vk.UNKNOWN_ABORT=!0,vk.INCOMPATIBLE_DB_VERSION=!1,vk);function xk(a,b,c,d,e){b=void 0===b?{}:b;c=void 0===c?sk[a]:c;d=void 0===d?uk[a]:d;e=void 0===e?wk[a]:e;Q.call(this,c,Object.assign({},{name:"YtIdbKnownError",isSw:void 0===self.document,isIframe:self!==self.top,type:a},b));this.type=a;this.message=c;this.level=d;this.h=e;Object.setPrototypeOf(this,xk.prototype)}
r(xk,Q);function yk(a,b){xk.call(this,"MISSING_OBJECT_STORES",{expectedObjectStores:b,foundObjectStores:a},sk.MISSING_OBJECT_STORES);Object.setPrototypeOf(this,yk.prototype)}
r(yk,xk);function zk(a,b){var c=Error.call(this);this.message=c.message;"stack"in c&&(this.stack=c.stack);this.index=a;this.objectStore=b;Object.setPrototypeOf(this,zk.prototype)}
r(zk,Error);var Ak=["The database connection is closing","Can't start a transaction on a closed database","A mutation operation was attempted on a database that did not allow mutations"];
function Bk(a,b,c,d){b=qk(b);var e=a instanceof Error?a:Error("Unexpected error: "+a);if(e instanceof xk)return e;a={objectStoreNames:c,dbName:b,dbVersion:d};if("QuotaExceededError"===e.name)return new xk("QUOTA_EXCEEDED",a);if(Ic&&"UnknownError"===e.name)return new xk("QUOTA_MAYBE_EXCEEDED",a);if(e instanceof zk)return new xk("MISSING_INDEX",Object.assign({},a,{objectStore:e.objectStore,index:e.index}));if("InvalidStateError"===e.name&&Ak.some(function(f){return e.message.includes(f)}))return new xk("EXECUTE_TRANSACTION_ON_CLOSED_DB",
a);
if("AbortError"===e.name)return new xk("UNKNOWN_ABORT",a,e.message);e.args=[Object.assign({},a,{name:"IdbError",Bb:e.name})];e.level="WARNING";return e}
function Ck(a,b,c){var d=dk();return new xk("IDB_NOT_SUPPORTED",{context:{caller:a,publicName:b,version:c,hasSucceededOnce:null==d?void 0:d.hasSucceededOnce}})}
;function Dk(a){if(!a)throw Error();throw a;}
function Ek(a){return a}
function Fk(a){this.h=a}
function Gk(a){function b(e){if("PENDING"===d.state.status){d.state={status:"REJECTED",reason:e};e=p(d.onRejected);for(var f=e.next();!f.done;f=e.next())f=f.value,f()}}
function c(e){if("PENDING"===d.state.status){d.state={status:"FULFILLED",value:e};e=p(d.h);for(var f=e.next();!f.done;f=e.next())f=f.value,f()}}
var d=this;this.state={status:"PENDING"};this.h=[];this.onRejected=[];a=a.h;try{a(c,b)}catch(e){b(e)}}
Gk.all=function(a){return new Gk(new Fk(function(b,c){var d=[],e=a.length;0===e&&b(d);for(var f={ma:0};f.ma<a.length;f={ma:f.ma},++f.ma)Hk(Gk.resolve(a[f.ma]).then(function(g){return function(h){d[g.ma]=h;e--;0===e&&b(d)}}(f)),function(g){c(g)})}))};
Gk.resolve=function(a){return new Gk(new Fk(function(b,c){a instanceof Gk?a.then(b,c):b(a)}))};
Gk.reject=function(a){return new Gk(new Fk(function(b,c){c(a)}))};
Gk.prototype.then=function(a,b){var c=this,d=null!=a?a:Ek,e=null!=b?b:Dk;return new Gk(new Fk(function(f,g){"PENDING"===c.state.status?(c.h.push(function(){Ik(c,c,d,f,g)}),c.onRejected.push(function(){Jk(c,c,e,f,g)})):"FULFILLED"===c.state.status?Ik(c,c,d,f,g):"REJECTED"===c.state.status&&Jk(c,c,e,f,g)}))};
function Hk(a,b){a.then(void 0,b)}
function Ik(a,b,c,d,e){try{if("FULFILLED"!==a.state.status)throw Error("calling handleResolve before the promise is fulfilled.");var f=c(a.state.value);f instanceof Gk?Kk(a,b,f,d,e):d(f)}catch(g){e(g)}}
function Jk(a,b,c,d,e){try{if("REJECTED"!==a.state.status)throw Error("calling handleReject before the promise is rejected.");var f=c(a.state.reason);f instanceof Gk?Kk(a,b,f,d,e):d(f)}catch(g){e(g)}}
function Kk(a,b,c,d,e){b===c?e(new TypeError("Circular promise chain detected.")):c.then(function(f){f instanceof Gk?Kk(a,b,f,d,e):d(f)},function(f){e(f)})}
;function Lk(a,b,c){function d(){c(a.error);f()}
function e(){b(a.result);f()}
function f(){try{a.removeEventListener("success",e),a.removeEventListener("error",d)}catch(g){}}
a.addEventListener("success",e);a.addEventListener("error",d)}
function Mk(a){return new Promise(function(b,c){Lk(a,b,c)})}
function Nk(a){return new Gk(new Fk(function(b,c){Lk(a,b,c)}))}
;function Ok(a,b){return new Gk(new Fk(function(c,d){function e(){var f=a?b(a):null;f?f.then(function(g){a=g;e()},d):c()}
e()}))}
;function Pk(a,b){this.h=a;this.options=b;this.transactionCount=0;this.j=Math.round(P());this.i=!1}
l=Pk.prototype;l.add=function(a,b,c){return Qk(this,[a],{mode:"readwrite",O:!0},function(d){return d.objectStore(a).add(b,c)})};
l.clear=function(a){return Qk(this,[a],{mode:"readwrite",O:!0},function(b){return b.objectStore(a).clear()})};
l.close=function(){this.h.close();var a;(null==(a=this.options)?0:a.closed)&&this.options.closed()};
l.count=function(a,b){return Qk(this,[a],{mode:"readonly",O:!0},function(c){return c.objectStore(a).count(b)})};
function Rk(a,b,c){a=a.h.createObjectStore(b,c);return new Sk(a)}
l.delete=function(a,b){return Qk(this,[a],{mode:"readwrite",O:!0},function(c){return c.objectStore(a).delete(b)})};
l.get=function(a,b){return Qk(this,[a],{mode:"readonly",O:!0},function(c){return c.objectStore(a).get(b)})};
function Tk(a,b){return Qk(a,["LogsRequestsStore"],{mode:"readwrite",O:!0},function(c){c=c.objectStore("LogsRequestsStore");return Nk(c.h.put(b,void 0))})}
l.objectStoreNames=function(){return Array.from(this.h.objectStoreNames)};
function Qk(a,b,c,d){var e,f,g,h,k,m,q,u,C,v,E,F;return w(function(I){switch(I.h){case 1:var R={mode:"readonly",O:!1,tag:"IDB_TRANSACTION_TAG_UNKNOWN"};"string"===typeof c?R.mode=c:Object.assign(R,c);e=R;a.transactionCount++;f=e.O?3:1;g=0;case 2:if(h){I.s(3);break}g++;k=Math.round(P());wa(I,4);m=a.h.transaction(b,e.mode);R=new Uk(m);R=Vk(R,d);return t(I,R,6);case 6:return q=I.i,u=Math.round(P()),Wk(a,k,u,g,void 0,b.join(),e),I.return(q);case 4:C=ya(I);v=Math.round(P());E=Bk(C,a.h.name,b.join(),a.h.version);
if((F=E instanceof xk&&!E.h)||g>=f)Wk(a,k,v,g,E,b.join(),e),h=E;I.s(2);break;case 3:return I.return(Promise.reject(h))}})}
function Wk(a,b,c,d,e,f,g){b=c-b;e?(e instanceof xk&&("QUOTA_EXCEEDED"===e.type||"QUOTA_MAYBE_EXCEEDED"===e.type)&&mk("QUOTA_EXCEEDED",{dbName:qk(a.h.name),objectStoreNames:f,transactionCount:a.transactionCount,transactionMode:g.mode}),e instanceof xk&&"UNKNOWN_ABORT"===e.type&&(c-=a.j,0>c&&c>=Math.pow(2,31)&&(c=0),mk("TRANSACTION_UNEXPECTEDLY_ABORTED",{objectStoreNames:f,transactionDuration:b,transactionCount:a.transactionCount,dbDuration:c}),a.i=!0),Xk(a,!1,d,f,b,g.tag),lk(e)):Xk(a,!0,d,f,b,g.tag)}
function Xk(a,b,c,d,e,f){mk("TRANSACTION_ENDED",{objectStoreNames:d,connectionHasUnknownAbortedTransaction:a.i,duration:e,isSuccessful:b,tryCount:c,tag:void 0===f?"IDB_TRANSACTION_TAG_UNKNOWN":f})}
l.getName=function(){return this.h.name};
function Sk(a){this.h=a}
l=Sk.prototype;l.add=function(a,b){return Nk(this.h.add(a,b))};
l.autoIncrement=function(){return this.h.autoIncrement};
l.clear=function(){return Nk(this.h.clear()).then(function(){})};
l.count=function(a){return Nk(this.h.count(a))};
function Yk(a,b){return Zk(a,{query:b},function(c){return c.delete().then(function(){return c.continue()})}).then(function(){})}
l.delete=function(a){return a instanceof IDBKeyRange?Yk(this,a):Nk(this.h.delete(a))};
l.get=function(a){return Nk(this.h.get(a))};
l.index=function(a){try{return new $k(this.h.index(a))}catch(b){if(b instanceof Error&&"NotFoundError"===b.name)throw new zk(a,this.h.name);throw b;}};
l.getName=function(){return this.h.name};
l.keyPath=function(){return this.h.keyPath};
function Zk(a,b,c){a=a.h.openCursor(b.query,b.direction);return al(a).then(function(d){return Ok(d,c)})}
function Uk(a){var b=this;this.h=a;this.j=new Map;this.i=!1;this.done=new Promise(function(c,d){b.h.addEventListener("complete",function(){c()});
b.h.addEventListener("error",function(e){e.currentTarget===e.target&&d(b.h.error)});
b.h.addEventListener("abort",function(){var e=b.h.error;if(e)d(e);else if(!b.i){e=xk;for(var f=b.h.objectStoreNames,g=[],h=0;h<f.length;h++){var k=f.item(h);if(null===k)throw Error("Invariant: item in DOMStringList is null");g.push(k)}e=new e("UNKNOWN_ABORT",{objectStoreNames:g.join(),dbName:b.h.db.name,mode:b.h.mode});d(e)}})})}
function Vk(a,b){var c=new Promise(function(d,e){try{Hk(b(a).then(function(f){d(f)}),e)}catch(f){e(f),a.abort()}});
return Promise.all([c,a.done]).then(function(d){return p(d).next().value})}
Uk.prototype.abort=function(){this.h.abort();this.i=!0;throw new xk("EXPLICIT_ABORT");};
Uk.prototype.objectStore=function(a){a=this.h.objectStore(a);var b=this.j.get(a);b||(b=new Sk(a),this.j.set(a,b));return b};
function $k(a){this.h=a}
l=$k.prototype;l.count=function(a){return Nk(this.h.count(a))};
l.delete=function(a){return bl(this,{query:a},function(b){return b.delete().then(function(){return b.continue()})})};
l.get=function(a){return Nk(this.h.get(a))};
l.getKey=function(a){return Nk(this.h.getKey(a))};
l.keyPath=function(){return this.h.keyPath};
l.unique=function(){return this.h.unique};
function bl(a,b,c){a=a.h.openCursor(void 0===b.query?null:b.query,void 0===b.direction?"next":b.direction);return al(a).then(function(d){return Ok(d,c)})}
function cl(a,b){this.request=a;this.cursor=b}
function al(a){return Nk(a).then(function(b){return b?new cl(a,b):null})}
l=cl.prototype;l.advance=function(a){this.cursor.advance(a);return al(this.request)};
l.continue=function(a){this.cursor.continue(a);return al(this.request)};
l.delete=function(){return Nk(this.cursor.delete()).then(function(){})};
l.getKey=function(){return this.cursor.key};
l.getValue=function(){return this.cursor.value};
l.update=function(a){return Nk(this.cursor.update(a))};function dl(a,b,c){return new Promise(function(d,e){function f(){C||(C=new Pk(g.result,{closed:u}));return C}
var g=void 0!==b?self.indexedDB.open(a,b):self.indexedDB.open(a);var h=c.blocked,k=c.blocking,m=c.zc,q=c.upgrade,u=c.closed,C;g.addEventListener("upgradeneeded",function(v){try{if(null===v.newVersion)throw Error("Invariant: newVersion on IDbVersionChangeEvent is null");if(null===g.transaction)throw Error("Invariant: transaction on IDbOpenDbRequest is null");v.dataLoss&&"none"!==v.dataLoss&&mk("IDB_DATA_CORRUPTED",{reason:v.dataLossMessage||"unknown reason",dbName:qk(a)});var E=f(),F=new Uk(g.transaction);
q&&q(E,function(I){return v.oldVersion<I&&v.newVersion>=I},F);
F.done.catch(function(I){e(I)})}catch(I){e(I)}});
g.addEventListener("success",function(){var v=g.result;k&&v.addEventListener("versionchange",function(){k(f())});
v.addEventListener("close",function(){mk("IDB_UNEXPECTEDLY_CLOSED",{dbName:qk(a),dbVersion:v.version});m&&m()});
d(f())});
g.addEventListener("error",function(){e(g.error)});
h&&g.addEventListener("blocked",function(){h()})})}
function el(a,b,c){c=void 0===c?{}:c;return dl(a,b,c)}
function fl(a,b){b=void 0===b?{}:b;var c,d,e,f;return w(function(g){if(1==g.h)return wa(g,2),c=self.indexedDB.deleteDatabase(a),d=b,(e=d.blocked)&&c.addEventListener("blocked",function(){e()}),t(g,Mk(c),4);
if(2!=g.h)return xa(g,0);f=ya(g);throw Bk(f,a,"",-1);})}
;function gl(a){return new Promise(function(b){Wj(function(){b()},a)})}
function hl(a,b){this.name=a;this.options=b;this.l=!0;this.m=this.o=0;this.i=500}
hl.prototype.j=function(a,b,c){c=void 0===c?{}:c;return el(a,b,c)};
hl.prototype.delete=function(a){a=void 0===a?{}:a;return fl(this.name,a)};
function il(a,b){return new xk("INCOMPATIBLE_DB_VERSION",{dbName:a.name,oldVersion:a.options.version,newVersion:b})}
function jl(a,b){if(!b)throw Ck("openWithToken",qk(a.name));return a.open()}
hl.prototype.open=function(){function a(){var f,g,h,k,m,q,u,C,v,E;return w(function(F){switch(F.h){case 1:return g=null!=(f=Error().stack)?f:"",wa(F,2),t(F,c.j(c.name,c.options.version,e),4);case 4:h=F.i;for(var I=c.options,R=[],O=p(Object.keys(I.xa)),S=O.next();!S.done;S=O.next()){S=S.value;var ka=I.xa[S],N=void 0===ka.ic?Number.MAX_VALUE:ka.ic;!(h.h.version>=ka.Va)||h.h.version>=N||h.h.objectStoreNames.contains(S)||R.push(S)}k=R;if(0===k.length){F.s(5);break}m=Object.keys(c.options.xa);q=h.objectStoreNames();
if(c.m<$h("ytidb_reopen_db_retries",0))return c.m++,h.close(),lk(new xk("DB_REOPENED_BY_MISSING_OBJECT_STORES",{dbName:c.name,expectedObjectStores:m,foundObjectStores:q})),F.return(a());if(!(c.o<$h("ytidb_remake_db_retries",1))){F.s(6);break}c.o++;if(!M("ytidb_remake_db_enable_backoff_delay")){F.s(7);break}return t(F,gl(c.i),8);case 8:c.i*=2;case 7:return t(F,c.delete(),9);case 9:return lk(new xk("DB_DELETED_BY_MISSING_OBJECT_STORES",{dbName:c.name,expectedObjectStores:m,foundObjectStores:q})),F.return(a());
case 6:throw new yk(q,m);case 5:return F.return(h);case 2:u=ya(F);if(u instanceof DOMException?"VersionError"!==u.name:"DOMError"in self&&u instanceof DOMError?"VersionError"!==u.name:!(u instanceof Object&&"message"in u)||"An attempt was made to open a database using a lower version than the existing version."!==u.message){F.s(10);break}return t(F,c.j(c.name,void 0,Object.assign({},e,{upgrade:void 0})),11);case 11:C=F.i;v=C.h.version;if(void 0!==c.options.version&&v>c.options.version+1)throw C.close(),
c.l=!1,il(c,v);return F.return(C);case 10:throw b(),u instanceof Error&&!M("ytidb_async_stack_killswitch")&&(u.stack=u.stack+"\n"+g.substring(g.indexOf("\n")+1)),Bk(u,c.name,"",null!=(E=c.options.version)?E:-1);}})}
function b(){c.h===d&&(c.h=void 0)}
var c=this;if(!this.l)throw il(this);if(this.h)return this.h;var d,e={blocking:function(f){f.close()},
closed:b,zc:b,upgrade:this.options.upgrade};return this.h=d=a()};var kl=new hl("YtIdbMeta",{xa:{databases:{Va:1}},upgrade:function(a,b){b(1)&&Rk(a,"databases",{keyPath:"actualName"})}});
function ll(a,b){var c;return w(function(d){if(1==d.h)return t(d,jl(kl,b),2);c=d.i;return d.return(Qk(c,["databases"],{O:!0,mode:"readwrite"},function(e){var f=e.objectStore("databases");return f.get(a.actualName).then(function(g){if(g?a.actualName!==g.actualName||a.publicName!==g.publicName||a.userIdentifier!==g.userIdentifier:1)return Nk(f.h.put(a,void 0)).then(function(){})})}))})}
function ml(a,b){var c;return w(function(d){if(1==d.h)return a?t(d,jl(kl,b),2):d.return();c=d.i;return d.return(c.delete("databases",a))})}
function nl(a,b){var c,d;return w(function(e){return 1==e.h?(c=[],t(e,jl(kl,b),2)):3!=e.h?(d=e.i,t(e,Qk(d,["databases"],{O:!0,mode:"readonly"},function(f){c.length=0;return Zk(f.objectStore("databases"),{},function(g){a(g.getValue())&&c.push(g.getValue());return g.continue()})}),3)):e.return(c)})}
function ol(a){return nl(function(b){return"LogsDatabaseV2"===b.publicName&&void 0!==b.userIdentifier},a)}
function pl(a,b,c){return nl(function(d){return c?void 0!==d.userIdentifier&&!a.includes(d.userIdentifier)&&c.includes(d.publicName):void 0!==d.userIdentifier&&!a.includes(d.userIdentifier)},b)}
function ql(a){var b,c;return w(function(d){if(1==d.h)return b=ok("YtIdbMeta hasAnyMeta other"),t(d,nl(function(e){return void 0!==e.userIdentifier&&e.userIdentifier!==b},a),2);
c=d.i;return d.return(0<c.length)})}
;var rl,sl=new function(){}(new function(){});
function tl(){var a,b,c,d;return w(function(e){switch(e.h){case 1:a=dk();if(null==(b=a)?0:b.hasSucceededOnce)return e.return(!0);var f;if(f=ak)f=/WebKit\/([0-9]+)/.exec(Rb()),f=!!(f&&600<=parseInt(f[1],10));f&&(f=/WebKit\/([0-9]+)/.exec(Rb()),f=!(f&&602<=parseInt(f[1],10)));if(f||tc)return e.return(!1);try{if(c=self,!(c.indexedDB&&c.IDBIndex&&c.IDBKeyRange&&c.IDBObjectStore))return e.return(!1)}catch(g){return e.return(!1)}if(!("IDBTransaction"in self&&"objectStoreNames"in IDBTransaction.prototype))return e.return(!1);
wa(e,2);d={actualName:"yt-idb-test-do-not-use",publicName:"yt-idb-test-do-not-use",userIdentifier:void 0};return t(e,ll(d,sl),4);case 4:return t(e,ml("yt-idb-test-do-not-use",sl),5);case 5:return e.return(!0);case 2:return ya(e),e.return(!1)}})}
function ul(){if(void 0!==rl)return rl;gk=!0;return rl=tl().then(function(a){gk=!1;var b;if(null!=(b=ck())&&b.h){var c;b={hasSucceededOnce:(null==(c=dk())?void 0:c.hasSucceededOnce)||a};var d;null==(d=ck())||d.set("LAST_RESULT_ENTRY_KEY",b,2592E3,!0)}return a})}
function vl(){return z("ytglobal.idbToken_")||void 0}
function wl(){var a=vl();return a?Promise.resolve(a):ul().then(function(b){(b=b?sl:void 0)&&y("ytglobal.idbToken_",b);return b})}
;var xl=0;function yl(a,b){xl||(xl=bf.N(function(){var c,d,e,f,g;return w(function(h){switch(h.h){case 1:return t(h,wl(),2);case 2:c=h.i;if(!c)return h.return();d=!0;wa(h,3);return t(h,pl(a,c,b),5);case 5:e=h.i;if(!e.length){d=!1;h.s(6);break}f=e[0];return t(h,fl(f.actualName),7);case 7:return t(h,ml(f.actualName,c),6);case 6:xa(h,4);break;case 3:g=ya(h),lk(g),d=!1;case 4:bf.U(xl),xl=0,d&&yl(a,b),h.h=0}})}))}
function zl(){var a;return w(function(b){return 1==b.h?t(b,wl(),2):(a=b.i)?b.return(ql(a)):b.return(!1)})}
new zd;function Al(a){if(!nk())throw a=new xk("AUTH_INVALID",{dbName:a}),lk(a),a;var b=ok();return{actualName:a+":"+b,publicName:a,userIdentifier:b}}
function Bl(a,b,c,d){var e,f,g,h,k,m;return w(function(q){switch(q.h){case 1:return f=null!=(e=Error().stack)?e:"",t(q,wl(),2);case 2:g=q.i;if(!g)throw h=Ck("openDbImpl",a,b),M("ytidb_async_stack_killswitch")||(h.stack=h.stack+"\n"+f.substring(f.indexOf("\n")+1)),lk(h),h;pk(a);k=c?{actualName:a,publicName:a,userIdentifier:void 0}:Al(a);wa(q,3);return t(q,ll(k,g),5);case 5:return t(q,el(k.actualName,b,d),6);case 6:return q.return(q.i);case 3:return m=ya(q),wa(q,7),t(q,ml(k.actualName,g),9);case 9:xa(q,
8);break;case 7:ya(q);case 8:throw m;}})}
function Cl(a,b,c){c=void 0===c?{}:c;return Bl(a,b,!1,c)}
function Dl(a,b,c){c=void 0===c?{}:c;return Bl(a,b,!0,c)}
function El(a,b){b=void 0===b?{}:b;var c,d;return w(function(e){if(1==e.h)return t(e,wl(),2);if(3!=e.h){c=e.i;if(!c)return e.return();pk(a);d=Al(a);return t(e,fl(d.actualName,b),3)}return t(e,ml(d.actualName,c),0)})}
function Fl(a,b,c){a=a.map(function(d){return w(function(e){return 1==e.h?t(e,fl(d.actualName,b),2):t(e,ml(d.actualName,c),0)})});
return Promise.all(a).then(function(){})}
function Gl(){var a=void 0===a?{}:a;var b,c;return w(function(d){if(1==d.h)return t(d,wl(),2);if(3!=d.h){b=d.i;if(!b)return d.return();pk("LogsDatabaseV2");return t(d,ol(b),3)}c=d.i;return t(d,Fl(c,a,b),0)})}
function Hl(a,b){b=void 0===b?{}:b;var c;return w(function(d){if(1==d.h)return t(d,wl(),2);if(3!=d.h){c=d.i;if(!c)return d.return();pk(a);return t(d,fl(a,b),3)}return t(d,ml(a,c),0)})}
;function Il(a){this.h=!1;this.potentialEsfErrorCounter=this.i=0;this.handleError=function(){};
this.qa=function(){};
this.now=Date.now;this.wa=!1;var b;this.Ib=null!=(b=a.Ib)?b:100;var c;this.Gb=null!=(c=a.Gb)?c:1;var d;this.Eb=null!=(d=a.Eb)?d:2592E6;var e;this.Cb=null!=(e=a.Cb)?e:12E4;var f;this.Fb=null!=(f=a.Fb)?f:5E3;var g;this.v=null!=(g=a.v)?g:void 0;this.Ka=!!a.Ka;var h;this.Ja=null!=(h=a.Ja)?h:.1;var k;this.Qa=null!=(k=a.Qa)?k:10;a.handleError&&(this.handleError=a.handleError);a.qa&&(this.qa=a.qa);a.wa&&(this.wa=a.wa);this.D=a.D;this.V=a.V;this.K=a.K;this.J=a.J;this.da=a.da;this.hb=a.hb;this.gb=a.gb;this.v&&
(!this.D||this.D("networkless_logging"))&&Jl(this)}
function Jl(a){a.v&&!a.wa&&(a.h=!0,a.Ka&&Math.random()<=a.Ja&&a.K.Pb(a.v),Kl(a),a.J.H()&&a.Aa(),a.J.W(a.hb,a.Aa.bind(a)),a.J.W(a.gb,a.mb.bind(a)))}
l=Il.prototype;l.writeThenSend=function(a,b){var c=this;b=void 0===b?{}:b;if(this.v&&this.h){var d={url:a,options:b,timestamp:this.now(),status:"NEW",sendCount:0};this.K.set(d,this.v).then(function(e){d.id=e;c.J.H()&&Ll(c,d)}).catch(function(e){Ll(c,d);
Ml(c,e)})}else this.da(a,b)};
l.sendThenWrite=function(a,b,c){var d=this;b=void 0===b?{}:b;if(this.v&&this.h){var e={url:a,options:b,timestamp:this.now(),status:"NEW",sendCount:0};this.D&&this.D("nwl_skip_retry")&&(e.skipRetry=c);if(this.J.H()||this.D&&this.D("nwl_aggressive_send_then_write")&&!e.skipRetry){if(!e.skipRetry){var f=b.onError?b.onError:function(){};
b.onError=function(g,h){return w(function(k){if(1==k.h)return t(k,d.K.set(e,d.v).catch(function(m){Ml(d,m)}),2);
f(g,h);k.h=0})}}this.da(a,b,e.skipRetry)}else this.K.set(e,this.v).catch(function(g){d.da(a,b,e.skipRetry);
Ml(d,g)})}else this.da(a,b,this.D&&this.D("nwl_skip_retry")&&c)};
l.sendAndWrite=function(a,b){var c=this;b=void 0===b?{}:b;if(this.v&&this.h){var d={url:a,options:b,timestamp:this.now(),status:"NEW",sendCount:0},e=!1,f=b.onSuccess?b.onSuccess:function(){};
d.options.onSuccess=function(g,h){void 0!==d.id?c.K.oa(d.id,c.v):e=!0;c.J.ca&&c.D&&c.D("vss_network_hint")&&c.J.ca(!0);f(g,h)};
this.da(d.url,d.options);this.K.set(d,this.v).then(function(g){d.id=g;e&&c.K.oa(d.id,c.v)}).catch(function(g){Ml(c,g)})}else this.da(a,b)};
l.Aa=function(){var a=this;if(!this.v)throw Ck("throttleSend");this.i||(this.i=this.V.N(function(){var b;return w(function(c){if(1==c.h)return t(c,a.K.vb("NEW",a.v),2);if(3!=c.h)return b=c.i,b?t(c,Ll(a,b),3):(a.mb(),c.return());a.i&&(a.i=0,a.Aa());c.h=0})},this.Ib))};
l.mb=function(){this.V.U(this.i);this.i=0};
function Ll(a,b){var c,d;return w(function(e){switch(e.h){case 1:if(!a.v)throw c=Ck("immediateSend"),c;if(void 0===b.id){e.s(2);break}return t(e,a.K.Zb(b.id,a.v),3);case 3:(d=e.i)?b=d:a.qa(Error("The request cannot be found in the database."));case 2:if(Nl(a,b,a.Eb)){e.s(4);break}a.qa(Error("Networkless Logging: Stored logs request expired age limit"));if(void 0===b.id){e.s(5);break}return t(e,a.K.oa(b.id,a.v),5);case 5:return e.return();case 4:b.skipRetry||(b=Ol(a,b));if(!b){e.s(0);break}if(!b.skipRetry||
void 0===b.id){e.s(8);break}return t(e,a.K.oa(b.id,a.v),8);case 8:a.da(b.url,b.options,!!b.skipRetry),e.h=0}})}
function Ol(a,b){if(!a.v)throw Ck("updateRequestHandlers");var c=b.options.onError?b.options.onError:function(){};
b.options.onError=function(e,f){var g,h,k;return w(function(m){switch(m.h){case 1:g=Pl(f);if(!(a.D&&a.D("nwl_consider_error_code")&&g||a.D&&!a.D("nwl_consider_error_code")&&a.potentialEsfErrorCounter<=a.Qa)){m.s(2);break}if(!a.J.ea){m.s(3);break}return t(m,a.J.ea(),3);case 3:if(a.J.H()){m.s(2);break}c(e,f);if(!a.D||!a.D("nwl_consider_error_code")||void 0===(null==(h=b)?void 0:h.id)){m.s(6);break}return t(m,a.K.ib(b.id,a.v,!1),6);case 6:return m.return();case 2:if(a.D&&a.D("nwl_consider_error_code")&&
!g&&a.potentialEsfErrorCounter>a.Qa)return m.return();a.potentialEsfErrorCounter++;if(void 0===(null==(k=b)?void 0:k.id)){m.s(8);break}return b.sendCount<a.Gb?t(m,a.K.ib(b.id,a.v),12):t(m,a.K.oa(b.id,a.v),8);case 12:a.V.N(function(){a.J.H()&&a.Aa()},a.Fb);
case 8:c(e,f),m.h=0}})};
var d=b.options.onSuccess?b.options.onSuccess:function(){};
b.options.onSuccess=function(e,f){var g;return w(function(h){if(1==h.h)return void 0===(null==(g=b)?void 0:g.id)?h.s(2):t(h,a.K.oa(b.id,a.v),2);a.J.ca&&a.D&&a.D("vss_network_hint")&&a.J.ca(!0);d(e,f);h.h=0})};
return b}
function Nl(a,b,c){b=b.timestamp;return a.now()-b>=c?!1:!0}
function Kl(a){if(!a.v)throw Ck("retryQueuedRequests");a.K.vb("QUEUED",a.v).then(function(b){b&&!Nl(a,b,a.Cb)?a.V.N(function(){return w(function(c){if(1==c.h)return void 0===b.id?c.s(2):t(c,a.K.ib(b.id,a.v),2);Kl(a);c.h=0})}):a.J.H()&&a.Aa()})}
function Ml(a,b){a.Kb&&!a.J.H()?a.Kb(b):a.handleError(b)}
function Pl(a){var b;return(a=null==a?void 0:null==(b=a.error)?void 0:b.code)&&400<=a&&599>=a?!1:!0}
;function Ql(a,b){this.version=a;this.args=b}
;function Rl(a,b){this.topic=a;this.h=b}
Rl.prototype.toString=function(){return this.topic};var Sl=z("ytPubsub2Pubsub2Instance")||new L;L.prototype.subscribe=L.prototype.subscribe;L.prototype.unsubscribeByKey=L.prototype.ta;L.prototype.publish=L.prototype.ja;L.prototype.clear=L.prototype.clear;y("ytPubsub2Pubsub2Instance",Sl);var Tl=z("ytPubsub2Pubsub2SubscribedKeys")||{};y("ytPubsub2Pubsub2SubscribedKeys",Tl);var Ul=z("ytPubsub2Pubsub2TopicToKeys")||{};y("ytPubsub2Pubsub2TopicToKeys",Ul);var Vl=z("ytPubsub2Pubsub2IsAsync")||{};y("ytPubsub2Pubsub2IsAsync",Vl);
y("ytPubsub2Pubsub2SkipSubKey",null);function Wl(a,b){var c=Xl();c&&c.publish.call(c,a.toString(),a,b)}
function Yl(a){var b=Zl,c=Xl();if(!c)return 0;var d=c.subscribe(b.toString(),function(e,f){var g=z("ytPubsub2Pubsub2SkipSubKey");g&&g==d||(g=function(){if(Tl[d])try{if(f&&b instanceof Rl&&b!=e)try{var h=b.h,k=f;if(!k.args||!k.version)throw Error("yt.pubsub2.Data.deserialize(): serializedData is incomplete.");try{if(!h.ia){var m=new h;h.ia=m.version}var q=h.ia}catch(I){}if(!q||k.version!=q)throw Error("yt.pubsub2.Data.deserialize(): serializedData version is incompatible.");try{q=Reflect;var u=q.construct;
var C=k.args,v=C.length;if(0<v){var E=Array(v);for(k=0;k<v;k++)E[k]=C[k];var F=E}else F=[];f=u.call(q,h,F)}catch(I){throw I.message="yt.pubsub2.Data.deserialize(): "+I.message,I;}}catch(I){throw I.message="yt.pubsub2.pubsub2 cross-binary conversion error for "+b.toString()+": "+I.message,I;}a.call(window,f)}catch(I){fi(I)}},Vl[b.toString()]?z("yt.scheduler.instance")?bf.N(g):zi(g,0):g())});
Tl[d]=!0;Ul[b.toString()]||(Ul[b.toString()]=[]);Ul[b.toString()].push(d);return d}
function $l(){var a=am,b=Yl(function(c){a.apply(void 0,arguments);bm(b)});
return b}
function bm(a){var b=Xl();b&&("number"===typeof a&&(a=[a]),fb(a,function(c){b.unsubscribeByKey(c);delete Tl[c]}))}
function Xl(){return z("ytPubsub2Pubsub2Instance")}
;function cm(a,b){hl.call(this,a,b);this.options=b;pk(a)}
r(cm,hl);function dm(a,b){var c;return function(){c||(c=new cm(a,b));return c}}
cm.prototype.j=function(a,b,c){c=void 0===c?{}:c;return(this.options.jb?Dl:Cl)(a,b,Object.assign({},c))};
cm.prototype.delete=function(a){a=void 0===a?{}:a;return(this.options.jb?Hl:El)(this.name,a)};
function em(a,b){return dm(a,b)}
;var fm;
function gm(){if(fm)return fm();var a={};fm=em("LogsDatabaseV2",{xa:(a.LogsRequestsStore={Va:2},a),jb:!1,upgrade:function(b,c,d){c(2)&&Rk(b,"LogsRequestsStore",{keyPath:"id",autoIncrement:!0});c(3);c(5)&&(d=d.objectStore("LogsRequestsStore"),d.h.indexNames.contains("newRequest")&&d.h.deleteIndex("newRequest"),d.h.createIndex("newRequestV2",["status","interface","timestamp"],{unique:!1}));c(7)&&b.h.objectStoreNames.contains("sapisid")&&b.h.deleteObjectStore("sapisid");c(9)&&b.h.objectStoreNames.contains("SWHealthLog")&&b.h.deleteObjectStore("SWHealthLog")},
version:9});return fm()}
;function hm(a){return jl(gm(),a)}
function im(a,b){var c,d,e,f;return w(function(g){if(1==g.h)return c={startTime:P(),transactionType:"YT_IDB_TRANSACTION_TYPE_WRITE"},t(g,hm(b),2);if(3!=g.h)return d=g.i,e=Object.assign({},a,{options:JSON.parse(JSON.stringify(a.options)),interface:A("INNERTUBE_CONTEXT_CLIENT_NAME",0)}),t(g,Tk(d,e),3);f=g.i;c.Ac=P();jm(c);return g.return(f)})}
function km(a,b){var c,d,e,f,g,h,k;return w(function(m){if(1==m.h)return c={startTime:P(),transactionType:"YT_IDB_TRANSACTION_TYPE_READ"},t(m,hm(b),2);if(3!=m.h)return d=m.i,e=A("INNERTUBE_CONTEXT_CLIENT_NAME",0),f=[a,e,0],g=[a,e,P()],h=IDBKeyRange.bound(f,g),k=void 0,t(m,Qk(d,["LogsRequestsStore"],{mode:"readwrite",O:!0},function(q){return bl(q.objectStore("LogsRequestsStore").index("newRequestV2"),{query:h,direction:"prev"},function(u){u.getValue()&&(k=u.getValue(),"NEW"===a&&(k.status="QUEUED",
u.update(k)))})}),3);
c.Ac=P();jm(c);return m.return(k)})}
function lm(a,b){var c;return w(function(d){if(1==d.h)return t(d,hm(b),2);c=d.i;return d.return(Qk(c,["LogsRequestsStore"],{mode:"readwrite",O:!0},function(e){var f=e.objectStore("LogsRequestsStore");return f.get(a).then(function(g){if(g)return g.status="QUEUED",Nk(f.h.put(g,void 0)).then(function(){return g})})}))})}
function mm(a,b,c){c=void 0===c?!0:c;var d;return w(function(e){if(1==e.h)return t(e,hm(b),2);d=e.i;return e.return(Qk(d,["LogsRequestsStore"],{mode:"readwrite",O:!0},function(f){var g=f.objectStore("LogsRequestsStore");return g.get(a).then(function(h){return h?(h.status="NEW",c&&(h.sendCount+=1),Nk(g.h.put(h,void 0)).then(function(){return h})):Gk.resolve(void 0)})}))})}
function nm(a,b){var c;return w(function(d){if(1==d.h)return t(d,hm(b),2);c=d.i;return d.return(c.delete("LogsRequestsStore",a))})}
function om(a){var b,c;return w(function(d){if(1==d.h)return t(d,hm(a),2);b=d.i;c=P()-2592E6;return t(d,Qk(b,["LogsRequestsStore"],{mode:"readwrite",O:!0},function(e){return Zk(e.objectStore("LogsRequestsStore"),{},function(f){if(f.getValue().timestamp<=c)return f.delete().then(function(){return f.continue()})})}),0)})}
function pm(){return w(function(a){return t(a,Gl(),0)})}
function jm(a){M("nwl_csi_killswitch")||.01>=Math.random()&&Wl("nwl_transaction_latency_payload",a)}
;var qm={},rm=em("ServiceWorkerLogsDatabase",{xa:(qm.SWHealthLog={Va:1},qm),jb:!0,upgrade:function(a,b){b(1)&&Rk(a,"SWHealthLog",{keyPath:"id",autoIncrement:!0}).h.createIndex("swHealthNewRequest",["interface","timestamp"],{unique:!1})},
version:1});function sm(a){return jl(rm(),a)}
function tm(a){var b,c;return w(function(d){if(1==d.h)return t(d,sm(a),2);b=d.i;c=P()-2592E6;return t(d,Qk(b,["SWHealthLog"],{mode:"readwrite",O:!0},function(e){return Zk(e.objectStore("SWHealthLog"),{},function(f){if(f.getValue().timestamp<=c)return f.delete().then(function(){return f.continue()})})}),0)})}
function um(a){var b;return w(function(c){if(1==c.h)return t(c,sm(a),2);b=c.i;return t(c,b.clear("SWHealthLog"),0)})}
;var vm={},wm=0;
function xm(a){var b=void 0===b?"":b;if(a)if(b)dj(a,void 0,"POST",b);else if(A("USE_NET_AJAX_FOR_PING_TRANSPORT",!1))dj(a,void 0,"GET","");else{b:{try{var c=new bb({url:a});if(c.j&&c.i||c.l){var d=bc(cc(5,a)),e;if(!(e=!d||!d.endsWith("/aclk"))){var f=a.search(mc),g=ic(a,0,"ri",f);if(0>g)var h=null;else{var k=a.indexOf("&",g);if(0>k||k>f)k=f;g+=3;h=decodeURIComponent(a.substr(g,k-g).replace(/\+/g," "))}e="1"!==h}var m=!e;break b}}catch(u){}m=!1}if(m){b:{try{if(window.navigator&&window.navigator.sendBeacon&&window.navigator.sendBeacon(a,
"")){var q=!0;break b}}catch(u){}q=!1}b=q?!0:!1}else b=!1;b||ym(a)}}
function ym(a){var b=new Image,c=""+wm++;vm[c]=b;b.onload=b.onerror=function(){delete vm[c]};
b.src=a}
;function zm(){this.h=new Map;this.i=!1}
function Am(){if(!zm.h){var a=z("yt.networkRequestMonitor.instance")||new zm;y("yt.networkRequestMonitor.instance",a);zm.h=a}return zm.h}
zm.prototype.requestComplete=function(a,b){b&&(this.i=!0);a=this.removeParams(a);this.h.get(a)||this.h.set(a,b)};
zm.prototype.isEndpointCFR=function(a){a=this.removeParams(a);return(a=this.h.get(a))?!1:!1===a&&this.i?!0:null};
zm.prototype.removeParams=function(a){return a.split("?")[0]};
zm.prototype.removeParams=zm.prototype.removeParams;zm.prototype.isEndpointCFR=zm.prototype.isEndpointCFR;zm.prototype.requestComplete=zm.prototype.requestComplete;zm.getInstance=Am;var Bm;function Cm(){Bm||(Bm=new Lj("yt.offline"));return Bm}
function Dm(a){if(M("offline_error_handling")){var b=Cm().get("errors",!0)||{};b[a.message]={name:a.name,stack:a.stack};a.level&&(b[a.message].level=a.level);Cm().set("errors",b,2592E3,!0)}}
function Em(){if(M("offline_error_handling")){var a=Cm().get("errors",!0);if(a){for(var b in a)if(a[b]){var c=new Q(b,"sent via offline_errors");c.name=a[b].name;c.stack=a[b].stack;c.level=a[b].level;fi(c)}Cm().set("errors",{},2592E3,!0)}}}
;var Fm=$h("network_polling_interval",3E4);function Gm(){Ve.call(this);var a=this;this.T=0;this.A=this.m=!1;this.j=this.Za();M("use_shared_nsm")?(this.i=af(),M("use_shared_nsm_and_keep_yt_online_updated")&&(this.i.W("networkstatus-online",function(){a.j=!0;a.A&&Em()}),this.i.W("networkstatus-offline",function(){a.j=!1}))):(Hm(this),Im(this))}
r(Gm,Ve);function Jm(){if(!Gm.h){var a=z("yt.networkStatusManager.instance")||new Gm;y("yt.networkStatusManager.instance",a);Gm.h=a}return Gm.h}
l=Gm.prototype;l.H=function(){if(M("use_shared_nsm")&&this.i){var a;return null==(a=this.i)?void 0:a.H()}return this.j};
l.ca=function(a){if(M("use_shared_nsm")&&this.i){var b;null!=(b=this.i)&&(b.i=a)}else a!==this.j&&(this.j=a)};
l.ac=function(a){!M("use_shared_nsm")&&(this.m=!0,void 0===a?0:a)&&(this.T||Km(this))};
l.Za=function(){var a=window.navigator.onLine;return void 0===a?!0:a};
l.Sb=function(){this.A=!0};
l.W=function(a,b){return M("use_shared_nsm")&&this.i?this.i.W(a,b):Ve.prototype.W.call(this,a,b)};
function Im(a){window.addEventListener("online",function(){return w(function(b){if(1==b.h)return t(b,a.ea(),2);a.A&&Em();b.h=0})})}
function Hm(a){window.addEventListener("offline",function(){return w(function(b){return t(b,a.ea(),0)})})}
function Km(a){a.T=Uj(function(){return w(function(b){if(1==b.h)return a.j?a.Za()||!a.m?b.s(3):t(b,a.ea(),3):t(b,a.ea(),3);Km(a);b.h=0})},Fm)}
l.ea=function(a){var b=this;if(M("use_shared_nsm")&&this.i){var c=Ze(this.i,a);c.then(function(d){M("use_cfr_monitor")&&Am().requestComplete("generate_204",d)});
return c}return this.u?this.u:this.u=new Promise(function(d){var e,f,g,h;return w(function(k){switch(k.h){case 1:return e=window.AbortController?new window.AbortController:void 0,g=null==(f=e)?void 0:f.signal,h=!1,wa(k,2,3),e&&(b.M=bf.N(function(){e.abort()},a||2E4)),t(k,fetch("/generate_204",{method:"HEAD",
signal:g}),5);case 5:h=!0;case 3:za(k);M("use_cfr_monitor")&&Am().requestComplete("generate_204",h);b.u=void 0;b.M&&bf.U(b.M);h!==b.j&&(b.j=h,b.j&&b.m?We(b,"ytnetworkstatus-online"):b.m&&We(b,"ytnetworkstatus-offline"));d(h);Aa(k);break;case 2:ya(k),h=!1,k.s(3)}})})};
Gm.prototype.sendNetworkCheckRequest=Gm.prototype.ea;Gm.prototype.listen=Gm.prototype.W;Gm.prototype.enableErrorFlushing=Gm.prototype.Sb;Gm.prototype.getWindowStatus=Gm.prototype.Za;Gm.prototype.monitorNetworkStatusChange=Gm.prototype.ac;Gm.prototype.networkStatusHint=Gm.prototype.ca;Gm.prototype.isNetworkAvailable=Gm.prototype.H;Gm.getInstance=Jm;function Lm(a){a=void 0===a?{}:a;Ve.call(this);var b=this;this.j=this.M=0;this.m="ytnetworkstatus-offline";this.u="ytnetworkstatus-online";M("use_shared_nsm")&&(this.m="networkstatus-offline",this.u="networkstatus-online");this.i=Jm();var c=z("yt.networkStatusManager.instance.monitorNetworkStatusChange").bind(this.i);c&&c(a.sb);a.zb&&(c=z("yt.networkStatusManager.instance.enableErrorFlushing").bind(this.i))&&c();if(c=z("yt.networkStatusManager.instance.listen").bind(this.i))a.Sa?(this.Sa=a.Sa,c(this.u,
function(){Mm(b,"publicytnetworkstatus-online")}),c(this.m,function(){Mm(b,"publicytnetworkstatus-offline")})):(c(this.u,function(){We(b,"publicytnetworkstatus-online")}),c(this.m,function(){We(b,"publicytnetworkstatus-offline")}))}
r(Lm,Ve);Lm.prototype.H=function(){var a=z("yt.networkStatusManager.instance.isNetworkAvailable");return a?a.bind(this.i)():!0};
Lm.prototype.ca=function(a){var b=z("yt.networkStatusManager.instance.networkStatusHint").bind(this.i);b&&b(a)};
Lm.prototype.ea=function(a){var b=this,c;return w(function(d){c=z("yt.networkStatusManager.instance.sendNetworkCheckRequest").bind(b.i);return M("skip_network_check_if_cfr")&&Am().isEndpointCFR("generate_204")?d.return(new Promise(function(e){var f;b.ca((null==(f=window.navigator)?void 0:f.onLine)||!0);e(b.H())})):c?d.return(c(a)):d.return(!0)})};
function Mm(a,b){a.Sa?a.j?(bf.U(a.M),a.M=bf.N(function(){a.A!==b&&(We(a,b),a.A=b,a.j=P())},a.Sa-(P()-a.j))):(We(a,b),a.A=b,a.j=P()):We(a,b)}
;var Nm;function Om(){Il.call(this,{K:{Pb:om,oa:nm,vb:km,Zb:lm,ib:mm,set:im},J:Pm(),handleError:fi,qa:gi,da:Qm,now:P,Kb:Dm,V:Zj(),hb:"publicytnetworkstatus-online",gb:"publicytnetworkstatus-offline",Ka:!0,Ja:.1,Qa:$h("potential_esf_error_limit",10),D:M,wa:!(nk()&&Rm())});this.j=new zd;M("networkless_immediately_drop_all_requests")&&pm();Hl("LogsDatabaseV2")}
r(Om,Il);function Sm(){var a=z("yt.networklessRequestController.instance");a||(a=new Om,y("yt.networklessRequestController.instance",a),M("networkless_logging")&&wl().then(function(b){a.v=b;Jl(a);a.j.resolve();a.Ka&&Math.random()<=a.Ja&&a.v&&tm(a.v);M("networkless_immediately_drop_sw_health_store")&&Tm(a)}));
return a}
Om.prototype.writeThenSend=function(a,b){b||(b={});nk()||(this.h=!1);Il.prototype.writeThenSend.call(this,a,b)};
Om.prototype.sendThenWrite=function(a,b,c){b||(b={});nk()||(this.h=!1);Il.prototype.sendThenWrite.call(this,a,b,c)};
Om.prototype.sendAndWrite=function(a,b){b||(b={});nk()||(this.h=!1);Il.prototype.sendAndWrite.call(this,a,b)};
Om.prototype.awaitInitialization=function(){return this.j.promise};
function Tm(a){var b;w(function(c){if(!a.v)throw b=Ck("clearSWHealthLogsDb"),b;return c.return(um(a.v).catch(function(d){a.handleError(d)}))})}
function Qm(a,b,c){M("use_cfr_monitor")&&Um(a,b);var d;if(null==(d=b.postParams)?0:d.requestTimeMs)b.postParams.requestTimeMs=Math.round(P());c&&0===Object.keys(b).length?xm(a):aj(a,b)}
function Pm(){Nm||(Nm=new Lm({zb:!0,sb:!0}));return Nm}
function Um(a,b){var c=b.onError?b.onError:function(){};
b.onError=function(e,f){Am().requestComplete(a,!1);c(e,f)};
var d=b.onSuccess?b.onSuccess:function(){};
b.onSuccess=function(e,f){Am().requestComplete(a,!0);d(e,f)}}
function Rm(){return M("embeds_web_nwl_disable_nocookie")?"www.youtube-nocookie.com"!==dc(document.location.toString()):!0}
;var Vm=!1,Wm=0,Xm=0,Ym,Zm=x.ytNetworklessLoggingInitializationOptions||{isNwlInitialized:Vm,potentialEsfErrorCounter:Xm};y("ytNetworklessLoggingInitializationOptions",Zm);
function $m(){var a;w(function(b){switch(b.h){case 1:return t(b,wl(),2);case 2:a=b.i;if(!a||!nk()&&!M("nwl_init_require_datasync_id_killswitch")||!Rm()){b.s(0);break}Vm=!0;Zm.isNwlInitialized=Vm;if(!M("use_new_nwl_initialization")){b.s(4);break}return t(b,Sm().awaitInitialization(),5);case 5:return b.return();case 4:return t(b,Hl("LogsDatabaseV2"),6);case 6:if(!(.1>=Math.random())){b.s(7);break}return t(b,om(a),8);case 8:return t(b,tm(a),7);case 7:an();bn().H()&&cn();bn().W("publicytnetworkstatus-online",
cn);bn().W("publicytnetworkstatus-offline",dn);if(!M("networkless_immediately_drop_sw_health_store")){b.s(10);break}return t(b,en(),10);case 10:if(M("networkless_immediately_drop_all_requests"))return t(b,pm(),0);b.s(0)}})}
function fn(a,b){function c(d){var e=bn().H();if(!gn()||!d||e&&M("vss_networkless_bypass_write"))hn(a,b);else{var f={url:a,options:b,timestamp:P(),status:"NEW",sendCount:0};im(f,d).then(function(g){f.id=g;bn().H()&&jn(f)}).catch(function(g){jn(f);
bn().H()?fi(g):Dm(g)})}}
b=void 0===b?{}:b;M("skip_is_supported_killswitch")?wl().then(function(d){c(d)}):c(vl())}
function kn(a,b){function c(d){if(gn()&&d){var e={url:a,options:b,timestamp:P(),status:"NEW",sendCount:0},f=!1,g=b.onSuccess?b.onSuccess:function(){};
e.options.onSuccess=function(k,m){M("use_cfr_monitor")&&Am().requestComplete(e.url,!0);void 0!==e.id?nm(e.id,d):f=!0;M("vss_network_hint")&&bn().ca(!0);g(k,m)};
if(M("use_cfr_monitor")){var h=b.onError?b.onError:function(){};
e.options.onError=function(k,m){Am().requestComplete(e.url,!1);h(k,m)}}hn(e.url,e.options);
im(e,d).then(function(k){e.id=k;f&&nm(e.id,d)}).catch(function(k){bn().H()?fi(k):Dm(k)})}else hn(a,b)}
b=void 0===b?{}:b;M("skip_is_supported_killswitch")?wl().then(function(d){c(d)}):c(vl())}
function cn(){var a=vl();if(!a)throw Ck("throttleSend");Wm||(Wm=bf.N(function(){var b;return w(function(c){if(1==c.h)return t(c,km("NEW",a),2);if(3!=c.h)return b=c.i,b?t(c,jn(b),3):(dn(),c.return());Wm&&(Wm=0,cn());c.h=0})},100))}
function dn(){bf.U(Wm);Wm=0}
function jn(a){var b,c,d;return w(function(e){switch(e.h){case 1:b=vl();if(!b)throw c=Ck("immediateSend"),c;if(void 0===a.id){e.s(2);break}return t(e,lm(a.id,b),3);case 3:(d=e.i)?a=d:gi(Error("The request cannot be found in the database."));case 2:if(ln(a,2592E6)){e.s(4);break}gi(Error("Networkless Logging: Stored logs request expired age limit"));if(void 0===a.id){e.s(5);break}return t(e,nm(a.id,b),5);case 5:return e.return();case 4:a.skipRetry||(a=mn(a));var f=a,g,h;if(null==f?0:null==(g=f.options)?
0:null==(h=g.postParams)?0:h.requestTimeMs)f.options.postParams.requestTimeMs=Math.round(P());a=f;if(!a){e.s(0);break}if(!a.skipRetry||void 0===a.id){e.s(8);break}return t(e,nm(a.id,b),8);case 8:hn(a.url,a.options,!!a.skipRetry),e.h=0}})}
function mn(a){var b=vl();if(!b)throw Ck("updateRequestHandlers");var c=a.options.onError?a.options.onError:function(){};
a.options.onError=function(e,f){var g,h,k;return w(function(m){switch(m.h){case 1:M("use_cfr_monitor")&&Am().requestComplete(a.url,!1);g=Pl(f);if(!(M("nwl_consider_error_code")&&g||!M("nwl_consider_error_code")&&nn()<=$h("potential_esf_error_limit",10))){m.s(2);break}if(M("skip_checking_network_on_cfr_failure")&&(!M("skip_checking_network_on_cfr_failure")||Am().isEndpointCFR(a.url))){m.s(3);break}return t(m,bn().ea(),3);case 3:if(bn().H()){m.s(2);break}c(e,f);if(!M("nwl_consider_error_code")||void 0===
(null==(h=a)?void 0:h.id)){m.s(6);break}return t(m,mm(a.id,b,!1),6);case 6:return m.return();case 2:if(M("nwl_consider_error_code")&&!g&&nn()>$h("potential_esf_error_limit",10))return m.return();z("ytNetworklessLoggingInitializationOptions")&&Zm.potentialEsfErrorCounter++;Xm++;if(void 0===(null==(k=a)?void 0:k.id)){m.s(8);break}return 1>a.sendCount?t(m,mm(a.id,b),12):t(m,nm(a.id,b),8);case 12:bf.N(function(){bn().H()&&cn()},5E3);
case 8:c(e,f),m.h=0}})};
var d=a.options.onSuccess?a.options.onSuccess:function(){};
a.options.onSuccess=function(e,f){var g;return w(function(h){if(1==h.h)return M("use_cfr_monitor")&&Am().requestComplete(a.url,!0),void 0===(null==(g=a)?void 0:g.id)?h.s(2):t(h,nm(a.id,b),2);M("vss_network_hint")&&bn().ca(!0);d(e,f);h.h=0})};
return a}
function ln(a,b){a=a.timestamp;return P()-a>=b?!1:!0}
function an(){var a=vl();if(!a)throw Ck("retryQueuedRequests");km("QUEUED",a).then(function(b){b&&!ln(b,12E4)?bf.N(function(){return w(function(c){if(1==c.h)return void 0===b.id?c.s(2):t(c,mm(b.id,a),2);an();c.h=0})}):bn().H()&&cn()})}
function en(){var a,b;return w(function(c){a=vl();if(!a)throw b=Ck("clearSWHealthLogsDb"),b;return c.return(um(a).catch(function(d){fi(d)}))})}
function bn(){if(M("use_new_nwl"))return Pm();Ym||(Ym=new Lm({zb:!0,sb:!0}));return Ym}
function hn(a,b,c){c&&0===Object.keys(b).length?xm(a):aj(a,b)}
function gn(){return z("ytNetworklessLoggingInitializationOptions")?Zm.isNwlInitialized:Vm}
function nn(){return z("ytNetworklessLoggingInitializationOptions")?Zm.potentialEsfErrorCounter:Xm}
;function on(a){var b=this;this.config_=null;a?this.config_=a:Bj()&&(this.config_=Cj());Uj(function(){Rj(b)},5E3)}
on.prototype.isReady=function(){!this.config_&&Bj()&&(this.config_=Cj());return!!this.config_};
function Sj(a,b,c,d){function e(E){E=void 0===E?!1:E;var F;if(d.retry&&"www.youtube-nocookie.com"!=h&&(E||M("skip_ls_gel_retry")||"application/json"!==g.headers["Content-Type"]||(F=Pj(b,c,m,k)),F)){var I=g.onSuccess,R=g.onFetchSuccess;g.onSuccess=function(O,S){Qj(F);I(O,S)};
c.onFetchSuccess=function(O,S){Qj(F);R(O,S)}}try{E&&d.retry&&!d.Ab.bypassNetworkless?(g.method="POST",d.Ab.writeThenSend?M("use_new_nwl_wts")?Sm().writeThenSend(v,g):fn(v,g):M("use_new_nwl_saw")?Sm().sendAndWrite(v,g):kn(v,g)):(g.method="POST",g.postParams||(g.postParams={}),aj(v,g))}catch(O){if("InvalidAccessError"==O.name)F&&(Qj(F),F=0),gi(Error("An extension is blocking network request."));
else throw O;}F&&Uj(function(){Rj(a)},5E3)}
!A("VISITOR_DATA")&&"visitor_id"!==b&&.01>Math.random()&&gi(new Q("Missing VISITOR_DATA when sending innertube request.",b,c,d));if(!a.isReady()){var f=new Q("innertube xhrclient not ready",b,c,d);fi(f);throw f;}var g={headers:d.headers||{},method:"POST",postParams:c,postBody:d.postBody,postBodyFormat:d.postBodyFormat||"JSON",onTimeout:function(){d.onTimeout()},
onFetchTimeout:d.onTimeout,onSuccess:function(E,F){if(d.onSuccess)d.onSuccess(F)},
onFetchSuccess:function(E){if(d.onSuccess)d.onSuccess(E)},
onError:function(E,F){if(d.onError)d.onError(F)},
onFetchError:function(E){if(d.onError)d.onError(E)},
timeout:d.timeout,withCredentials:!0};g.headers["Content-Type"]||(g.headers["Content-Type"]="application/json");var h="";(f=a.config_.Wb)&&(h=f);var k=a.config_.Yb||!1,m=Jj(k,h,d);Object.assign(g.headers,m);(f=g.headers.Authorization)&&!h&&(g.headers["x-origin"]=window.location.origin);var q="/youtubei/"+a.config_.innertubeApiVersion+"/"+b,u={alt:"json"},C=a.config_.Xb&&f;C=C&&f.startsWith("Bearer");C||(u.key=a.config_.innertubeApiKey);var v=si(""+h+q,u||{},!0);M("use_new_nwl")&&Sm().h||!M("use_new_nwl")&&
gn()?ul().then(function(E){e(E)}):e(!1)}
;var pn={appSettingsCaptured:!0,visualElementAttached:!0,visualElementGestured:!0,visualElementHidden:!0,visualElementShown:!0,flowEvent:!0,visualElementStateChanged:!0,playbackAssociated:!0,youThere:!0,accountStateChangeSignedIn:!0,accountStateChangeSignedOut:!0},qn={latencyActionBaselined:!0,latencyActionInfo:!0,latencyActionTicked:!0,bedrockRepetitiveActionTimed:!0,adsClientStateChange:!0,streamzIncremented:!0,mdxDialAdditionalDataUpdateEvent:!0,tvhtml5WatchKeyEvent:!0,tvhtml5VideoSeek:!0,tokenRefreshEvent:!0,
adNotify:!0,adNotifyFilled:!0,tvhtml5LaunchUrlComponentChanged:!0,bedrockResourceConsumptionSnapshot:!0,deviceStartupMetrics:!0,mdxSignIn:!0,tvhtml5KeyboardLogging:!0,tvhtml5StartupSoundEvent:!0,tvhtml5LiveChatStatus:!0,tvhtml5DeviceStorageStatus:!0,tvhtml5LocalStorage:!0,directSignInEvent:!0,finalPayload:!0,tvhtml5SearchCompleted:!0,tvhtml5KeyboardPerformance:!0,adNotifyFailure:!0,latencyActionSpan:!0,tvhtml5AccountDialogOpened:!0,tvhtml5ApiTest:!0};var rn=0,sn=vc?"webkit":uc?"moz":sc?"ms":rc?"o":"";y("ytDomDomGetNextId",z("ytDomDomGetNextId")||function(){return++rn});var tn={stopImmediatePropagation:1,stopPropagation:1,preventMouseEvent:1,preventManipulation:1,preventDefault:1,layerX:1,layerY:1,screenX:1,screenY:1,scale:1,rotation:1,webkitMovementX:1,webkitMovementY:1};
function un(a){this.type="";this.state=this.source=this.data=this.currentTarget=this.relatedTarget=this.target=null;this.charCode=this.keyCode=0;this.metaKey=this.shiftKey=this.ctrlKey=this.altKey=!1;this.rotation=this.clientY=this.clientX=0;this.scale=1;this.changedTouches=this.touches=null;try{if(a=a||window.event){this.event=a;for(var b in a)b in tn||(this[b]=a[b]);this.scale=a.scale;this.rotation=a.rotation;var c=a.target||a.srcElement;c&&3==c.nodeType&&(c=c.parentNode);this.target=c;var d=a.relatedTarget;
if(d)try{d=d.nodeName?d:null}catch(e){d=null}else"mouseover"==this.type?d=a.fromElement:"mouseout"==this.type&&(d=a.toElement);this.relatedTarget=d;this.clientX=void 0!=a.clientX?a.clientX:a.pageX;this.clientY=void 0!=a.clientY?a.clientY:a.pageY;this.keyCode=a.keyCode?a.keyCode:a.which;this.charCode=a.charCode||("keypress"==this.type?this.keyCode:0);this.altKey=a.altKey;this.ctrlKey=a.ctrlKey;this.shiftKey=a.shiftKey;this.metaKey=a.metaKey;this.h=a.pageX;this.i=a.pageY}}catch(e){}}
function vn(a){if(document.body&&document.documentElement){var b=document.body.scrollTop+document.documentElement.scrollTop;a.h=a.clientX+(document.body.scrollLeft+document.documentElement.scrollLeft);a.i=a.clientY+b}}
un.prototype.preventDefault=function(){this.event&&(this.event.returnValue=!1,this.event.preventDefault&&this.event.preventDefault())};
un.prototype.stopPropagation=function(){this.event&&(this.event.cancelBubble=!0,this.event.stopPropagation&&this.event.stopPropagation())};
un.prototype.stopImmediatePropagation=function(){this.event&&(this.event.cancelBubble=!0,this.event.stopImmediatePropagation&&this.event.stopImmediatePropagation())};var ob=x.ytEventsEventsListeners||{};y("ytEventsEventsListeners",ob);var wn=x.ytEventsEventsCounter||{count:0};y("ytEventsEventsCounter",wn);
function xn(a,b,c,d){d=void 0===d?{}:d;a.addEventListener&&("mouseenter"!=b||"onmouseenter"in document?"mouseleave"!=b||"onmouseenter"in document?"mousewheel"==b&&"MozBoxSizing"in document.documentElement.style&&(b="MozMousePixelScroll"):b="mouseout":b="mouseover");return nb(function(e){var f="boolean"===typeof e[4]&&e[4]==!!d,g=Ra(e[4])&&Ra(d)&&ub(e[4],d);return!!e.length&&e[0]==a&&e[1]==b&&e[2]==c&&(f||g)})}
var yn=db(function(){var a=!1;try{var b=Object.defineProperty({},"capture",{get:function(){a=!0}});
window.addEventListener("test",null,b)}catch(c){}return a});
function zn(a,b,c,d){d=void 0===d?{}:d;if(!a||!a.addEventListener&&!a.attachEvent)return"";var e=xn(a,b,c,d);if(e)return e;e=++wn.count+"";var f=!("mouseenter"!=b&&"mouseleave"!=b||!a.addEventListener||"onmouseenter"in document);var g=f?function(h){h=new un(h);if(!Md(h.relatedTarget,function(k){return k==a}))return h.currentTarget=a,h.type=b,c.call(a,h)}:function(h){h=new un(h);
h.currentTarget=a;return c.call(a,h)};
g=ei(g);a.addEventListener?("mouseenter"==b&&f?b="mouseover":"mouseleave"==b&&f?b="mouseout":"mousewheel"==b&&"MozBoxSizing"in document.documentElement.style&&(b="MozMousePixelScroll"),yn()||"boolean"===typeof d?a.addEventListener(b,g,d):a.addEventListener(b,g,!!d.capture)):a.attachEvent("on"+b,g);ob[e]=[a,b,c,g,d];return e}
function An(a){a&&("string"==typeof a&&(a=[a]),fb(a,function(b){if(b in ob){var c=ob[b],d=c[0],e=c[1],f=c[3];c=c[4];d.removeEventListener?yn()||"boolean"===typeof c?d.removeEventListener(e,f,c):d.removeEventListener(e,f,!!c.capture):d.detachEvent&&d.detachEvent("on"+e,f);delete ob[b]}}))}
;var Bn=window.ytcsi&&window.ytcsi.now?window.ytcsi.now:window.performance&&window.performance.timing&&window.performance.now&&window.performance.timing.navigationStart?function(){return window.performance.timing.navigationStart+window.performance.now()}:function(){return(new Date).getTime()};function Cn(a){this.L=a;this.i=null;this.m=0;this.A=null;this.u=0;this.j=[];for(a=0;4>a;a++)this.j.push(0);this.l=0;this.T=zn(window,"mousemove",Xa(this.Y,this));a=Xa(this.M,this);"function"===typeof a&&(a=ei(a));this.fa=window.setInterval(a,25)}
Za(Cn,K);Cn.prototype.Y=function(a){void 0===a.h&&vn(a);var b=a.h;void 0===a.i&&vn(a);this.i=new Id(b,a.i)};
Cn.prototype.M=function(){if(this.i){var a=Bn();if(0!=this.m){var b=this.A,c=this.i,d=b.x-c.x;b=b.y-c.y;d=Math.sqrt(d*d+b*b)/(a-this.m);this.j[this.l]=.5<Math.abs((d-this.u)/this.u)?1:0;for(c=b=0;4>c;c++)b+=this.j[c]||0;3<=b&&this.L();this.u=d}this.m=a;this.A=this.i;this.l=(this.l+1)%4}};
Cn.prototype.I=function(){window.clearInterval(this.fa);An(this.T)};var Dn={};
function En(a){var b=void 0===a?{}:a;a=void 0===b.ec?!1:b.ec;b=void 0===b.Tb?!0:b.Tb;if(null==z("_lact",window)){var c=parseInt(A("LACT"),10);c=isFinite(c)?Date.now()-Math.max(c,0):-1;y("_lact",c,window);y("_fact",c,window);-1==c&&Fn();zn(document,"keydown",Fn);zn(document,"keyup",Fn);zn(document,"mousedown",Fn);zn(document,"mouseup",Fn);a?zn(window,"touchmove",function(){Gn("touchmove",200)},{passive:!0}):(zn(window,"resize",function(){Gn("resize",200)}),b&&zn(window,"scroll",function(){Gn("scroll",200)}));
new Cn(function(){Gn("mouse",100)});
zn(document,"touchstart",Fn,{passive:!0});zn(document,"touchend",Fn,{passive:!0})}}
function Gn(a,b){Dn[a]||(Dn[a]=!0,bf.N(function(){Fn();Dn[a]=!1},b))}
function Fn(){null==z("_lact",window)&&En();var a=Date.now();y("_lact",a,window);-1==z("_fact",window)&&y("_fact",a,window);(a=z("ytglobal.ytUtilActivityCallback_"))&&a()}
function Hn(){var a=z("_lact",window);return null==a?-1:Math.max(Date.now()-a,0)}
;var In=x.ytPubsubPubsubInstance||new L,Jn=x.ytPubsubPubsubSubscribedKeys||{},Kn=x.ytPubsubPubsubTopicToKeys||{},Ln=x.ytPubsubPubsubIsSynchronous||{};function Mn(a,b){var c=Nn();if(c&&b){var d=c.subscribe(a,function(){var e=arguments;var f=function(){Jn[d]&&b.apply&&"function"==typeof b.apply&&b.apply(window,e)};
try{Ln[a]?f():zi(f,0)}catch(g){fi(g)}},void 0);
Jn[d]=!0;Kn[a]||(Kn[a]=[]);Kn[a].push(d);return d}return 0}
function On(a){var b=Nn();b&&("number"===typeof a?a=[a]:"string"===typeof a&&(a=[parseInt(a,10)]),fb(a,function(c){b.unsubscribeByKey(c);delete Jn[c]}))}
function Pn(a,b){var c=Nn();c&&c.publish.apply(c,arguments)}
function Qn(a){var b=Nn();if(b)if(b.clear(a),a)ho(a);else for(var c in Kn)ho(c)}
function Nn(){return x.ytPubsubPubsubInstance}
function ho(a){Kn[a]&&(a=Kn[a],fb(a,function(b){Jn[b]&&delete Jn[b]}),a.length=0)}
L.prototype.subscribe=L.prototype.subscribe;L.prototype.unsubscribeByKey=L.prototype.ta;L.prototype.publish=L.prototype.ja;L.prototype.clear=L.prototype.clear;y("ytPubsubPubsubInstance",In);y("ytPubsubPubsubTopicToKeys",Kn);y("ytPubsubPubsubIsSynchronous",Ln);y("ytPubsubPubsubSubscribedKeys",Jn);var Go=$h("initial_gel_batch_timeout",2E3),Ho=Math.pow(2,16)-1,Io=void 0;function Jo(){this.j=this.h=this.i=0}
var Ko=new Jo,Lo=new Jo,Mo=!0,No=x.ytLoggingTransportGELQueue_||new Map;y("ytLoggingTransportGELQueue_",No);var Oo=x.ytLoggingTransportGELProtoQueue_||new Map;y("ytLoggingTransportGELProtoQueue_",Oo);var Po=x.ytLoggingTransportTokensToCttTargetIds_||{};y("ytLoggingTransportTokensToCttTargetIds_",Po);var Qo=x.ytLoggingTransportTokensToJspbCttTargetIds_||{};y("ytLoggingTransportTokensToJspbCttTargetIds_",Qo);
function Ro(a,b){if("log_event"===a.endpoint){var c=So(a),d=No.get(c)||[];No.set(c,d);d.push(a.payload);To(b,d,c)}}
function Uo(a,b){if("log_event"===a.endpoint){var c=So(a,!0),d=Oo.get(c)||[];Oo.set(c,d);a=sd(a.payload);d.push(a);To(b,d,c,!0)}}
function To(a,b,c,d){d=void 0===d?!1:d;a&&(Io=new a);a=$h("tvhtml5_logging_max_batch")||$h("web_logging_max_batch")||100;var e=P(),f=d?Lo.j:Ko.j;b.length>=a?Vo({writeThenSend:!0},M("flush_only_full_queue")?c:void 0,d):10<=e-f&&(Wo(d),d?Lo.j=e:Ko.j=e)}
function Xo(a,b){if("log_event"===a.endpoint){var c=So(a),d=new Map;d.set(c,[a.payload]);b&&(Io=new b);return new Xf(function(e){Io&&Io.isReady()?Yo(d,e,{bypassNetworkless:!0},!0):e()})}}
function Zo(a,b){if("log_event"===a.endpoint){var c=So(a,!0),d=new Map;d.set(c,[sd(a.payload)]);b&&(Io=new b);return new Xf(function(e){Io&&Io.isReady()?$o(d,e,{bypassNetworkless:!0},!0):e()})}}
function So(a,b){var c="";if(a.va)c="visitorOnlyApprovedKey";else if(a.cttAuthInfo){if(void 0===b?0:b){b=a.cttAuthInfo.token;c=a.cttAuthInfo;var d=new Eh;c.videoId?d.setVideoId(c.videoId):c.playlistId&&jd(d,2,Fh,c.playlistId);Qo[b]=d}else b=a.cttAuthInfo,c={},b.videoId?c.videoId=b.videoId:b.playlistId&&(c.playlistId=b.playlistId),Po[a.cttAuthInfo.token]=c;c=a.cttAuthInfo.token}return c}
function Vo(a,b,c){a=void 0===a?{}:a;c=void 0===c?!1:c;new Xf(function(d){c?(Ai(Lo.i),Ai(Lo.h),Lo.h=0):(Ai(Ko.i),Ai(Ko.h),Ko.h=0);if(Io&&Io.isReady())if(void 0!==b)if(c){var e=new Map,f=Oo.get(b)||[];e.set(b,f);$o(e,d,a);Oo.delete(b)}else e=new Map,f=No.get(b)||[],e.set(b,f),Yo(e,d,a),No.delete(b);else c?($o(Oo,d,a),Oo.clear()):(Yo(No,d,a),No.clear());else Wo(c),d()})}
function Wo(a){a=void 0===a?!1:a;if(M("web_gel_timeout_cap")&&(!a&&!Ko.h||a&&!Lo.h)){var b=zi(function(){Vo({writeThenSend:!0},void 0,a)},6E4);
a?Lo.h=b:Ko.h=b}Ai(a?Lo.i:Ko.i);b=A("LOGGING_BATCH_TIMEOUT",$h("web_gel_debounce_ms",1E4));M("shorten_initial_gel_batch_timeout")&&Mo&&(b=Go);b=zi(function(){Vo({writeThenSend:!0},void 0,a)},b);
a?Lo.i=b:Ko.i=b}
function Yo(a,b,c,d){var e=Io;c=void 0===c?{}:c;var f=Math.round(P()),g=a.size;a=p(a);for(var h=a.next();!h.done;h=a.next()){var k=p(h.value);h=k.next().value;var m=k=k.next().value;k=wb({context:Dj(e.config_||Cj())});k.events=m;(m=Po[h])&&ap(k,h,m);delete Po[h];h="visitorOnlyApprovedKey"===h;bp(k,f,h);cp(c);Sj(e,"log_event",k,dp(c,h,function(){g--;g||b()},function(){g--;
g||b()},d));
Mo=!1}}
function $o(a,b,c,d){var e=Io;c=void 0===c?{}:c;var f=Math.round(P()),g=a.size;a=p(a);for(var h=a.next();!h.done;h=a.next()){var k=p(h.value);h=k.next().value;var m=k=k.next().value;k=new Gh;var q=Ij(e.config_||Cj());H(k,1,q);m=ep(m);for(q=0;q<m.length;q++)od(k,3,Ah,m[q]);(m=Qo[h])&&fp(k,h,m);delete Qo[h];h="visitorOnlyApprovedKey"===h;gp(k,f,h);cp(c);k=sd(k);h=dp(c,h,function(){g--;g||b()},function(){g--;
g||b()},d);
h.headers={"Content-Type":"application/json+protobuf"};h.postBodyFormat="JSPB";h.postBody=k;Sj(e,"log_event","",h);Mo=!1}}
function cp(a){M("always_send_and_write")&&(a.writeThenSend=!1)}
function dp(a,b,c,d,e){return{retry:!0,onSuccess:c,onError:d,Ab:a,va:b,No:!!e,headers:{},postBodyFormat:"",postBody:""}}
function bp(a,b,c){a.requestTimeMs=String(b);M("unsplit_gel_payloads_in_logs")&&(a.unsplitGelPayloadsInLogs=!0);!c&&(b=A("EVENT_ID"))&&(c=hp(),a.serializedClientEventId={serializedEventId:b,clientCounter:String(c)})}
function gp(a,b,c){D(a,2,b);if(!c&&(b=A("EVENT_ID"))){c=hp();var d=new Dh;D(d,1,b);D(d,2,c);H(a,5,d)}}
function hp(){var a=A("BATCH_CLIENT_COUNTER")||0;a||(a=Math.floor(Math.random()*Ho/2));a++;a>Ho&&(a=1);Xh("BATCH_CLIENT_COUNTER",a);return a}
function ap(a,b,c){if(c.videoId)var d="VIDEO";else if(c.playlistId)d="PLAYLIST";else return;a.credentialTransferTokenTargetId=c;a.context=a.context||{};a.context.user=a.context.user||{};a.context.user.credentialTransferTokens=[{token:b,scope:d}]}
function fp(a,b,c){if(hd(c,1===kd(c,Fh)?1:-1))var d=1;else if(c.getPlaylistId())d=2;else return;H(a,4,c);a=ld(a,Rg,1)||new Rg;c=ld(a,Pg,3)||new Pg;var e=new Og;e.setToken(b);D(e,1,d);od(c,12,Og,e);H(a,3,c)}
function ep(a){for(var b=[],c=0;c<a.length;c++)try{var d=b,e=d.push;var f=String(a[c]),g=Ah;if(null==f||""==f)var h=new g;else{var k=JSON.parse(f);if(!Array.isArray(k))throw Error("Expected to deserialize an Array but got "+Pa(k)+": "+k);rd=k;var m=new g(k);rd=null;h=m}e.call(d,h)}catch(q){fi(new Q("Transport failed to deserialize "+String(a[c])))}return b}
;var ip=x.ytLoggingGelSequenceIdObj_||{};y("ytLoggingGelSequenceIdObj_",ip);
function jp(a,b,c,d){d=void 0===d?{}:d;if(M("lr_drop_other_and_business_payloads")){if(qn[a]||pn[a])return}else if(M("lr_drop_other_payloads")&&qn[a])return;var e={},f=Math.round(d.timestamp||P());e.eventTimeMs=f<Number.MAX_SAFE_INTEGER?f:0;e[a]=b;a=Hn();e.context={lastActivityMs:String(d.timestamp||!isFinite(a)?-1:a)};M("log_sequence_info_on_gel_web")&&d.X&&(a=e.context,b=d.X,b={index:kp(b),groupKey:b},a.sequence=b,d.tb&&delete ip[d.X]);(d.nc?Xo:Ro)({endpoint:"log_event",payload:e,cttAuthInfo:d.cttAuthInfo,
va:d.va},c)}
function kp(a){ip[a]=a in ip?ip[a]+1:0;return ip[a]}
;function kk(a,b,c){c=void 0===c?{}:c;var d=on;A("ytLoggingEventsDefaultDisabled",!1)&&on==on&&(d=null);jp(a,b,d,c)}
;var lp=[{fb:function(a){return"Cannot read property '"+a.key+"'"},
Pa:{Error:[{regexp:/(Permission denied) to access property "([^']+)"/,groups:["reason","key"]}],TypeError:[{regexp:/Cannot read property '([^']+)' of (null|undefined)/,groups:["key","value"]},{regexp:/\u65e0\u6cd5\u83b7\u53d6\u672a\u5b9a\u4e49\u6216 (null|undefined) \u5f15\u7528\u7684\u5c5e\u6027\u201c([^\u201d]+)\u201d/,groups:["value","key"]},{regexp:/\uc815\uc758\ub418\uc9c0 \uc54a\uc74c \ub610\ub294 (null|undefined) \ucc38\uc870\uc778 '([^']+)' \uc18d\uc131\uc744 \uac00\uc838\uc62c \uc218 \uc5c6\uc2b5\ub2c8\ub2e4./,
groups:["value","key"]},{regexp:/No se puede obtener la propiedad '([^']+)' de referencia nula o sin definir/,groups:["key"]},{regexp:/Unable to get property '([^']+)' of (undefined or null) reference/,groups:["key","value"]},{regexp:/(null) is not an object \(evaluating '(?:([^.]+)\.)?([^']+)'\)/,groups:["value","base","key"]}]}},{fb:function(a){return"Cannot call '"+a.key+"'"},
Pa:{TypeError:[{regexp:/(?:([^ ]+)?\.)?([^ ]+) is not a function/,groups:["base","key"]},{regexp:/([^ ]+) called on (null or undefined)/,groups:["key","value"]},{regexp:/Object (.*) has no method '([^ ]+)'/,groups:["base","key"]},{regexp:/Object doesn't support property or method '([^ ]+)'/,groups:["key"]},{regexp:/\u30aa\u30d6\u30b8\u30a7\u30af\u30c8\u306f '([^']+)' \u30d7\u30ed\u30d1\u30c6\u30a3\u307e\u305f\u306f\u30e1\u30bd\u30c3\u30c9\u3092\u30b5\u30dd\u30fc\u30c8\u3057\u3066\u3044\u307e\u305b\u3093/,
groups:["key"]},{regexp:/\uac1c\uccb4\uac00 '([^']+)' \uc18d\uc131\uc774\ub098 \uba54\uc11c\ub4dc\ub97c \uc9c0\uc6d0\ud558\uc9c0 \uc54a\uc2b5\ub2c8\ub2e4./,groups:["key"]}]}},{fb:function(a){return a.key+" is not defined"},
Pa:{ReferenceError:[{regexp:/(.*) is not defined/,groups:["key"]},{regexp:/Can't find variable: (.*)/,groups:["key"]}]}}];var np={ha:[],ga:[{ka:mp,weight:500}]};function mp(a){if("JavaException"===a.name)return!0;a=a.stack;return a.includes("chrome://")||a.includes("chrome-extension://")||a.includes("moz-extension://")}
;function op(){this.ga=[];this.ha=[]}
var pp;function qp(){if(!pp){var a=pp=new op;a.ha.length=0;a.ga.length=0;np.ha&&a.ha.push.apply(a.ha,np.ha);np.ga&&a.ga.push.apply(a.ga,np.ga)}return pp}
;var rp=new L;function sp(a){function b(){return a.charCodeAt(d++)}
var c=a.length,d=0;do{var e=tp(b);if(Infinity===e)break;var f=e>>3;switch(e&7){case 0:e=tp(b);if(2===f)return e;break;case 1:if(2===f)return;d+=8;break;case 2:e=tp(b);if(2===f)return a.substr(d,e);d+=e;break;case 5:if(2===f)return;d+=4;break;default:return}}while(d<c)}
function tp(a){var b=a(),c=b&127;if(128>b)return c;b=a();c|=(b&127)<<7;if(128>b)return c;b=a();c|=(b&127)<<14;if(128>b)return c;b=a();return 128>b?c|(b&127)<<21:Infinity}
;function up(a,b,c,d){if(a)if(Array.isArray(a)){var e=d;for(d=0;d<a.length&&!(a[d]&&(e+=vp(d,a[d],b,c),500<e));d++);d=e}else if("object"===typeof a)for(e in a){if(a[e]){var f=a[e];var g=b;var h=c;g="string"!==typeof f||"clickTrackingParams"!==e&&"trackingParams"!==e?0:(f=sp(atob(f.replace(/-/g,"+").replace(/_/g,"/"))))?vp(e+".ve",f,g,h):0;d+=g;d+=vp(e,a[e],b,c);if(500<d)break}}else c[b]=wp(a),d+=c[b].length;else c[b]=wp(a),d+=c[b].length;return d}
function vp(a,b,c,d){c+="."+a;a=wp(b);d[c]=a;return c.length+a.length}
function wp(a){try{return("string"===typeof a?a:String(JSON.stringify(a))).substr(0,500)}catch(b){return"unable to serialize "+typeof a+" ("+b.message+")"}}
;var xp=x.ytLoggingGelSequenceIdObj_||{};y("ytLoggingGelSequenceIdObj_",xp);function yp(a,b,c){c=void 0===c?{}:c;var d=Math.round(c.timestamp||P());D(a,1,d<Number.MAX_SAFE_INTEGER?d:0);var e=Hn();d=new zh;D(d,1,c.timestamp||!isFinite(e)?-1:e);if(M("log_sequence_info_on_gel_web")&&c.X){e=c.X;var f=kp(e),g=new yh;D(g,2,f);D(g,1,e);H(d,3,g);c.tb&&delete xp[c.X]}H(a,33,d);(c.nc?Zo:Uo)({endpoint:"log_event",payload:a,cttAuthInfo:c.cttAuthInfo,va:c.va},b)}
;function zp(a,b){b=void 0===b?{}:b;var c=!1;A("ytLoggingEventsDefaultDisabled",!1)&&on===on&&(c=!0);yp(a,c?null:on,b)}
;function Ap(a,b,c){var d=new Ah;nd(d,73,Bh,a);c?yp(d,c,b):zp(d,b)}
function Bp(a,b,c){var d=new Ah;nd(d,78,Bh,a);c?yp(d,c,b):zp(d,b)}
function Cp(a,b,c){var d=new Ah;nd(d,208,Bh,a);c?yp(d,c,b):zp(d,b)}
function Dp(a,b,c){var d=new Ah;nd(d,156,Bh,a);c?yp(d,c,b):zp(d,b)}
function Ep(a,b,c){var d=new Ah;nd(d,215,Bh,a);c?yp(d,c,b):zp(d,b)}
function Fp(a,b,c){var d=new Ah;nd(d,111,Bh,a);c?yp(d,c,b):zp(d,b)}
;var Gp=new Set,Hp=0,Ip=0,Jp=0,Kp=[],Lp=["PhantomJS","Googlebot","TO STOP THIS SECURITY SCAN go/scan"];function jk(a){Mp(a)}
function Np(a){Mp(a,"WARNING")}
function Mp(a,b,c,d,e,f){f=void 0===f?{}:f;f.name=c||A("INNERTUBE_CONTEXT_CLIENT_NAME",1);f.version=d||A("INNERTUBE_CONTEXT_CLIENT_VERSION");var g=f||{},h=void 0===b?"ERROR":b;h=void 0===h?"ERROR":h;if(a){a.hasOwnProperty("level")&&a.level&&(h=a.level);if(M("console_log_js_exceptions")){var k=[];k.push("Name: "+a.name);k.push("Message: "+a.message);a.hasOwnProperty("params")&&k.push("Error Params: "+JSON.stringify(a.params));a.hasOwnProperty("args")&&k.push("Error args: "+JSON.stringify(a.args));
k.push("File name: "+a.fileName);k.push("Stacktrace: "+a.stack);window.console.log(k.join("\n"),a)}if(!(5<=Hp)){var m=Kp,q=te(a),u=q.message||"Unknown Error",C=q.name||"UnknownError",v=q.stack||a.i||"Not available";if(v.startsWith(C+": "+u)){var E=v.split("\n");E.shift();v=E.join("\n")}var F=q.lineNumber||"Not available",I=q.fileName||"Not available",R=v,O=0;if(a.hasOwnProperty("args")&&a.args&&a.args.length)for(var S=0;S<a.args.length&&!(O=up(a.args[S],"params."+S,g,O),500<=O);S++);else if(a.hasOwnProperty("params")&&
a.params){var ka=a.params;if("object"===typeof a.params)for(var N in ka){if(ka[N]){var Ca="params."+N,Oa=wp(ka[N]);g[Ca]=Oa;O+=Ca.length+Oa.length;if(500<O)break}}else g.params=wp(ka)}if(m.length)for(var va=0;va<m.length&&!(O=up(m[va],"params.context."+va,g,O),500<=O);va++);navigator.vendor&&!g.hasOwnProperty("vendor")&&(g["device.vendor"]=navigator.vendor);var G={message:u,name:C,lineNumber:F,fileName:I,stack:R,params:g,sampleWeight:1},Da=Number(a.columnNumber);isNaN(Da)||(G.lineNumber=G.lineNumber+
":"+Da);if("IGNORED"===a.level)var ua=0;else a:{for(var Rn=qp(),Sn=p(Rn.ha),Di=Sn.next();!Di.done;Di=Sn.next()){var Tn=Di.value;if(G.message&&G.message.match(Tn.So)){ua=Tn.weight;break a}}for(var Un=p(Rn.ga),Ei=Un.next();!Ei.done;Ei=Un.next()){var Vn=Ei.value;if(Vn.ka(G)){ua=Vn.weight;break a}}ua=1}G.sampleWeight=ua;for(var Wn=p(lp),Fi=Wn.next();!Fi.done;Fi=Wn.next()){var Gi=Fi.value;if(Gi.Pa[G.name])for(var Xn=p(Gi.Pa[G.name]),Hi=Xn.next();!Hi.done;Hi=Xn.next()){var Yn=Hi.value,Nf=G.message.match(Yn.regexp);
if(Nf){G.params["params.error.original"]=Nf[0];for(var Ii=Yn.groups,Zn={},Yc=0;Yc<Ii.length;Yc++)Zn[Ii[Yc]]=Nf[Yc+1],G.params["params.error."+Ii[Yc]]=Nf[Yc+1];G.message=Gi.fb(Zn);break}}}G.params||(G.params={});var $n=qp();G.params["params.errorServiceSignature"]="msg="+$n.ha.length+"&cb="+$n.ga.length;G.params["params.serviceWorker"]="false";x.document&&x.document.querySelectorAll&&(G.params["params.fscripts"]=String(document.querySelectorAll("script:not([nonce])").length));Db("sample").constructor!==
Bb&&(G.params["params.fconst"]="true");window.yterr&&"function"===typeof window.yterr&&window.yterr(G);if(0!==G.sampleWeight&&!Gp.has(G.message)){if("ERROR"===h){rp.ja("handleError",G);if(M("record_app_crashed_web")&&0===Jp&&1===G.sampleWeight)if(Jp++,M("errors_via_jspb")){var Ji=new dh;D(Ji,1,1);if(!M("report_client_error_with_app_crash_ks")){var ao=new Zg;D(ao,1,G.message);var bo=new $g;H(bo,3,ao);var co=new ah;H(co,5,bo);var eo=new bh;H(eo,9,co);H(Ji,4,eo)}var fo=new Ah;nd(fo,20,Bh,Ji);zp(fo)}else{var go=
{appCrashType:"APP_CRASH_TYPE_BREAKPAD"};M("report_client_error_with_app_crash_ks")||(go.systemHealth={crashData:{clientError:{logMessage:{message:G.message}}}});kk("appCrashed",go)}Ip++}else"WARNING"===h&&rp.ja("handleWarning",G);if(M("kevlar_gel_error_routing"))a:{var Xd=h;if(M("errors_via_jspb")){if(Op())var io=void 0;else{var Zc=new Wg;D(Zc,1,G.stack);G.fileName&&D(Zc,4,G.fileName);var qb=G.lineNumber&&G.lineNumber.split?G.lineNumber.split(":"):[];0!==qb.length&&(1!==qb.length||isNaN(Number(qb[0]))?
2!==qb.length||isNaN(Number(qb[0]))||isNaN(Number(qb[1]))||(D(Zc,2,Number(qb[0])),D(Zc,3,Number(qb[1]))):D(Zc,2,Number(qb[0])));var jc=new Zg;D(jc,1,G.message);D(jc,3,G.name);D(jc,6,G.sampleWeight);"ERROR"===Xd?D(jc,2,2):"WARNING"===Xd?D(jc,2,1):D(jc,2,0);var Ki=new Xg;D(Ki,1,!0);nd(Ki,3,Yg,Zc);var Jb=new Tg;D(Jb,3,window.location.href);for(var jo=A("FEXP_EXPERIMENTS",[]),Li=0;Li<jo.length;Li++){var At=jo[Li];Wc(Jb);id(Jb,5).push(At)}var Mi=A("LATEST_ECATCHER_SERVICE_TRACKING_PARAMS");if(!Yh()&&Mi)for(var ko=
p(Object.keys(Mi)),kc=ko.next();!kc.done;kc=ko.next()){var lo=kc.value,Ni=new Vg;D(Ni,1,lo);Ni.setValue(String(Mi[lo]));od(Jb,4,Vg,Ni)}var Oi=G.params;if(Oi){var mo=p(Object.keys(Oi));for(kc=mo.next();!kc.done;kc=mo.next()){var no=kc.value,Pi=new Vg;D(Pi,1,"client."+no);Pi.setValue(String(Oi[no]));od(Jb,4,Vg,Pi)}}var oo=A("SERVER_NAME"),po=A("SERVER_VERSION");if(oo&&po){var Qi=new Vg;D(Qi,1,"server.name");Qi.setValue(oo);od(Jb,4,Vg,Qi);var Ri=new Vg;D(Ri,1,"server.version");Ri.setValue(po);od(Jb,
4,Vg,Ri)}var Of=new $g;H(Of,1,Jb);H(Of,2,Ki);H(Of,3,jc);io=Of}var qo=io;if(!qo)break a;var ro=new Ah;nd(ro,163,Bh,qo);zp(ro)}else{if(Op())var so=void 0;else{var Yd={stackTrace:G.stack};G.fileName&&(Yd.filename=G.fileName);var rb=G.lineNumber&&G.lineNumber.split?G.lineNumber.split(":"):[];0!==rb.length&&(1!==rb.length||isNaN(Number(rb[0]))?2!==rb.length||isNaN(Number(rb[0]))||isNaN(Number(rb[1]))||(Yd.lineNumber=Number(rb[0]),Yd.columnNumber=Number(rb[1])):Yd.lineNumber=Number(rb[0]));var Si={level:"ERROR_LEVEL_UNKNOWN",
message:G.message,errorClassName:G.name,sampleWeight:G.sampleWeight};"ERROR"===Xd?Si.level="ERROR_LEVEL_ERROR":"WARNING"===Xd&&(Si.level="ERROR_LEVEL_WARNNING");var Bt={isObfuscated:!0,browserStackInfo:Yd},$c={pageUrl:window.location.href,kvPairs:[]};A("FEXP_EXPERIMENTS")&&($c.experimentIds=A("FEXP_EXPERIMENTS"));var Ti=A("LATEST_ECATCHER_SERVICE_TRACKING_PARAMS");if(!Yh()&&Ti)for(var to=p(Object.keys(Ti)),lc=to.next();!lc.done;lc=to.next()){var uo=lc.value;$c.kvPairs.push({key:uo,value:String(Ti[uo])})}var Ui=
G.params;if(Ui){var vo=p(Object.keys(Ui));for(lc=vo.next();!lc.done;lc=vo.next()){var wo=lc.value;$c.kvPairs.push({key:"client."+wo,value:String(Ui[wo])})}}var xo=A("SERVER_NAME"),yo=A("SERVER_VERSION");xo&&yo&&($c.kvPairs.push({key:"server.name",value:xo}),$c.kvPairs.push({key:"server.version",value:yo}));so={errorMetadata:$c,stackTrace:Bt,logMessage:Si}}var zo=so;if(!zo)break a;kk("clientError",zo)}("ERROR"===Xd||M("errors_flush_gel_always_killswitch"))&&Vo(void 0,void 0,!1)}if(!M("suppress_error_204_logging")){var Zd=
G.params||{},Kb={urlParams:{a:"logerror",t:"jserror",type:G.name,msg:G.message.substr(0,250),line:G.lineNumber,level:h,"client.name":Zd.name},postParams:{url:A("PAGE_NAME",window.location.href),file:G.fileName},method:"POST"};Zd.version&&(Kb["client.version"]=Zd.version);if(Kb.postParams){G.stack&&(Kb.postParams.stack=G.stack);for(var Ao=p(Object.keys(Zd)),Vi=Ao.next();!Vi.done;Vi=Ao.next()){var Bo=Vi.value;Kb.postParams["client."+Bo]=Zd[Bo]}var Wi=A("LATEST_ECATCHER_SERVICE_TRACKING_PARAMS");if(Wi)for(var Co=
p(Object.keys(Wi)),Xi=Co.next();!Xi.done;Xi=Co.next()){var Do=Xi.value;Kb.postParams[Do]=Wi[Do]}var Eo=A("SERVER_NAME"),Fo=A("SERVER_VERSION");Eo&&Fo&&(Kb.postParams["server.name"]=Eo,Kb.postParams["server.version"]=Fo)}aj(A("ECATCHER_REPORT_HOST","")+"/error_204",Kb)}try{Gp.add(G.message)}catch($u){}Hp++}}}}
function Op(){for(var a=p(Lp),b=a.next();!b.done;b=a.next())if(bk(b.value.toLowerCase()))return!0;return!1}
function Pp(a){var b=Ja.apply(1,arguments),c=a;c.args||(c.args=[]);c.args.push.apply(c.args,fa(b))}
;function Qp(){this.register=new Map}
function Rp(a){a=p(a.register.values());for(var b=a.next();!b.done;b=a.next())b.value.Vo("ABORTED")}
Qp.prototype.clear=function(){Rp(this);this.register.clear()};
var Sp=new Qp;var Tp=Date.now().toString();
function Up(){a:{if(window.crypto&&window.crypto.getRandomValues)try{var a=Array(16),b=new Uint8Array(16);window.crypto.getRandomValues(b);for(var c=0;c<a.length;c++)a[c]=b[c];var d=a;break a}catch(e){}d=Array(16);for(a=0;16>a;a++){b=Date.now();for(c=0;c<b%23;c++)d[a]=Math.random();d[a]=Math.floor(256*Math.random())}if(Tp)for(a=1,b=0;b<Tp.length;b++)d[a%16]=d[a%16]^d[(a-1)%16]/4^Tp.charCodeAt(b),a++}a=[];for(b=0;b<d.length;b++)a.push("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_".charAt(d[b]&63));
return a.join("")}
;var Vp=x.ytLoggingDocDocumentNonce_;Vp||(Vp=Up(),y("ytLoggingDocDocumentNonce_",Vp));var Wp=Vp;var Xp={Ag:0,qd:1,Ad:2,ek:3,Cg:4,ko:5,Uk:6,vm:7,Xl:8,0:"DEFAULT",1:"CHAT",2:"CONVERSATIONS",3:"MINIPLAYER",4:"DIALOG",5:"VOZ",6:"MUSIC_WATCH_TABS",7:"SHARE",8:"PUSH_NOTIFICATIONS"};function Yp(a){this.h=a}
function Zp(a){return new Yp({trackingParams:a})}
Yp.prototype.getAsJson=function(){var a={};void 0!==this.h.trackingParams?a.trackingParams=this.h.trackingParams:(a.veType=this.h.veType,void 0!==this.h.veCounter&&(a.veCounter=this.h.veCounter),void 0!==this.h.elementIndex&&(a.elementIndex=this.h.elementIndex));void 0!==this.h.dataElement&&(a.dataElement=this.h.dataElement.getAsJson());void 0!==this.h.youtubeData&&(a.youtubeData=this.h.youtubeData);return a};
Yp.prototype.getAsJspb=function(){var a=new fh;void 0!==this.h.trackingParams?D(a,1,this.h.trackingParams):(void 0!==this.h.veType&&D(a,2,this.h.veType),void 0!==this.h.veCounter&&D(a,6,this.h.veCounter),void 0!==this.h.elementIndex&&D(a,3,this.h.elementIndex));if(void 0!==this.h.dataElement){var b=this.h.dataElement.getAsJspb();H(a,7,b)}void 0!==this.h.youtubeData&&H(a,8,this.h.jspbYoutubeData);return a};
Yp.prototype.toString=function(){return JSON.stringify(this.getAsJson())};
Yp.prototype.isClientVe=function(){return!this.h.trackingParams&&!!this.h.veType};function $p(a){a=void 0===a?0:a;return 0===a?"client-screen-nonce":"client-screen-nonce."+a}
function aq(a){a=void 0===a?0:a;return 0===a?"ROOT_VE_TYPE":"ROOT_VE_TYPE."+a}
function bq(a){return A(aq(void 0===a?0:a))}
y("yt_logging_screen.getRootVeType",bq);function cq(a){return(a=bq(void 0===a?0:a))?new Yp({veType:a,youtubeData:void 0,jspbYoutubeData:void 0}):null}
function dq(){var a=A("csn-to-ctt-auth-info");a||(a={},Xh("csn-to-ctt-auth-info",a));return a}
function eq(a){a=A($p(void 0===a?0:a));if(!a&&!A("USE_CSN_FALLBACK",!0))return null;a||(a="UNDEFINED_CSN");return a?a:null}
y("yt_logging_screen.getCurrentCsn",eq);function fq(a,b,c){var d=dq();(c=eq(c))&&delete d[c];b&&(d[a]=b)}
function gq(a){return dq()[a]}
y("yt_logging_screen.getCttAuthInfo",gq);
function hq(a,b,c,d){c=void 0===c?0:c;if(a!==A($p(c))||b!==A(aq(c)))fq(a,d,c),Xh($p(c),a),Xh(aq(c),b),b=function(){setTimeout(function(){if(a)if(M("web_time_via_jspb")){var e=new gh;D(e,1,Wp);D(e,2,a);M("use_default_heartbeat_client")?Fp(e):Fp(e,void 0,on)}else e={clientDocumentNonce:Wp,clientScreenNonce:a},M("use_default_heartbeat_client")?kk("foregroundHeartbeatScreenAssociated",e):jp("foregroundHeartbeatScreenAssociated",e,on)},0)},"requestAnimationFrame"in window?window.requestAnimationFrame(b):
b()}
y("yt_logging_screen.setCurrentScreen",hq);var iq=window.yt&&window.yt.msgs_||window.ytcfg&&window.ytcfg.msgs||{};y("yt.msgs_",iq);function jq(a){Mh(iq,arguments)}
;var kq={pd:3611,Dc:27686,Ec:85013,Fc:23462,Hc:42016,Ic:62407,Jc:26926,Gc:43781,Kc:51236,Lc:79148,Mc:50160,Nc:77504,Zc:87907,bd:18630,cd:54445,dd:80935,ed:105675,fd:37521,gd:147285,hd:47786,jd:98349,kd:123695,ld:6827,md:29434,nd:7282,od:124448,sd:32276,rd:76278,td:147868,ud:147869,vd:93911,wd:106531,xd:27259,yd:27262,zd:27263,Bd:21759,Cd:27107,Dd:62936,Ed:49568,Fd:38408,Gd:80637,Hd:68727,Id:68728,Jd:80353,Kd:80356,Ld:74610,Md:45707,Nd:83962,Od:83970,Pd:46713,Qd:89711,Rd:74612,Sd:93265,Td:74611,Ud:131380,
Wd:128979,Xd:139311,Yd:128978,Vd:131391,Zd:105350,be:139312,ce:134800,ae:131392,ee:113533,ge:93252,he:99357,je:94521,ke:114252,le:113532,me:94522,ie:94583,ne:88E3,oe:139580,pe:93253,qe:93254,re:94387,se:94388,te:93255,ue:97424,de:72502,we:110111,xe:76019,ze:117092,Ae:117093,ye:89431,Be:110466,Ce:77240,De:60508,Ee:148123,Fe:148124,Ge:137401,He:137402,Ie:137046,Je:73393,Ke:113534,Le:92098,Me:131381,Ne:84517,Oe:83759,Pe:80357,Qe:86113,Re:72598,Se:72733,Te:107349,Ue:124275,Ve:118203,We:133275,Xe:133274,
Ye:133272,Ze:133273,af:133276,bf:144507,cf:143247,df:143248,ef:143249,ff:143250,gf:143251,hf:144401,kf:117431,jf:133797,lf:128572,mf:133405,nf:117429,pf:117430,qf:117432,rf:120080,sf:117259,tf:121692,uf:145656,vf:145655,wf:145653,xf:145654,yf:145657,zf:132972,Af:133051,Bf:133658,Cf:132971,Df:97615,Ff:143359,Ef:143356,Hf:143361,Gf:143358,Jf:143360,If:143357,Kf:142303,Lf:143353,Mf:143354,Nf:144479,Of:143355,Pf:31402,Rf:133624,Sf:146477,Tf:133623,Uf:133622,Qf:133621,Vf:84774,Wf:95117,Xf:98930,Yf:98931,
Zf:98932,ag:43347,cg:129889,dg:45474,eg:100352,fg:84758,gg:98443,hg:117985,ig:74613,jg:74614,kg:64502,lg:136032,mg:74615,ng:74616,og:122224,pg:74617,qg:77820,rg:74618,sg:93278,tg:93274,ug:93275,vg:93276,wg:22110,xg:29433,yg:133798,zg:132295,Bg:120541,Dg:82047,Eg:113550,Fg:75836,Gg:75837,Hg:42352,Ig:84512,Jg:76065,Kg:75989,Lg:16623,Mg:32594,Ng:27240,Og:32633,Pg:74858,Rg:3945,Qg:16989,Sg:45520,Tg:25488,Ug:25492,Vg:25494,Wg:55760,Xg:14057,Yg:18451,Zg:57204,ah:57203,bh:17897,dh:57205,eh:18198,fh:17898,
gh:17909,hh:43980,ih:46220,jh:11721,kh:147994,lh:49954,mh:96369,nh:3854,oh:56251,ph:25624,Gh:16906,Hh:99999,Ih:68172,Jh:27068,Kh:47973,Lh:72773,Mh:26970,Nh:26971,Oh:96805,Ph:17752,Qh:73233,Rh:109512,Sh:22256,Th:14115,Uh:22696,Vh:89278,Wh:89277,Xh:109513,Yh:43278,Zh:43459,ai:43464,bi:89279,ci:43717,di:55764,fi:22255,gi:147912,hi:89281,ii:40963,ji:43277,ki:43442,li:91824,mi:120137,ni:96367,oi:36850,ri:72694,si:37414,ti:36851,wi:124863,vi:121343,xi:73491,yi:54473,zi:43375,Ai:46674,Bi:143815,Ci:139095,
Di:144402,Ei:32473,Fi:72901,Gi:72906,Hi:50947,Ii:50612,Ji:50613,Ki:50942,Li:84938,Mi:84943,Ni:84939,Oi:84941,Pi:84944,Qi:84940,Ri:84942,Si:35585,Ti:51926,Ui:79983,Vi:63238,Wi:18921,Xi:63241,Yi:57893,Zi:41182,aj:135732,bj:33424,cj:22207,dj:42993,ej:36229,fj:22206,gj:22205,hj:18993,ij:19001,jj:18990,kj:18991,lj:18997,mj:18725,nj:19003,oj:36874,pj:44763,qj:33427,rj:67793,sj:22182,tj:37091,uj:34650,vj:50617,wj:47261,xj:22287,yj:25144,zj:97917,Aj:62397,Bj:125598,Cj:137935,Dj:36961,Ej:108035,Fj:27426,Gj:27857,
Hj:27846,Ij:27854,Jj:69692,Kj:61411,Lj:39299,Mj:38696,Nj:62520,Oj:36382,Pj:108701,Qj:50663,Rj:36387,Sj:14908,Tj:37533,Uj:105443,Vj:61635,Wj:62274,Xj:133818,Yj:65702,Zj:65703,ak:65701,bk:76256,ck:37671,dk:49953,fk:36216,gk:28237,hk:39553,ik:29222,jk:26107,kk:38050,lk:26108,nk:120745,mk:26109,pk:26110,qk:66881,rk:28236,sk:14586,tk:57929,uk:74723,vk:44098,wk:44099,zk:23528,Ak:61699,xk:134104,yk:134103,Bk:59149,Ck:101951,Dk:97346,Ek:118051,Fk:95102,Gk:64882,Hk:119505,Ik:63595,Jk:63349,Kk:95101,Lk:75240,
Mk:27039,Nk:68823,Ok:21537,Pk:83464,Qk:75707,Rk:83113,Sk:101952,Tk:101953,Vk:79610,Wk:125755,Xk:24402,Yk:24400,Zk:32925,al:57173,bl:122502,dl:145268,fl:138480,il:64423,jl:64424,kl:33986,ll:100828,ml:129089,nl:21409,rl:135155,sl:135156,ul:135157,vl:135158,wl:135159,xl:135160,yl:135161,zl:135162,Al:135163,Bl:135164,Cl:135165,Dl:135166,ol:11070,pl:11074,ql:17880,El:14001,Gl:30709,Hl:30707,Il:30711,Jl:30710,Kl:30708,Fl:26984,Ll:146143,Ml:63648,Nl:63649,Ol:51879,Pl:111059,Ql:5754,Rl:20445,Tl:130975,Sl:130976,
Ul:110386,Vl:113746,Wl:66557,Yl:17310,Zl:28631,am:21589,bm:68012,cm:60480,dm:138664,em:141121,fm:31571,gm:141978,hm:76980,im:41577,jm:45469,km:38669,lm:13768,mm:13777,nm:141842,om:62985,pm:4724,qm:59369,rm:43927,sm:43928,tm:12924,um:100355,xm:56219,ym:27669,zm:10337,wm:47896,Am:122629,Cm:139723,Bm:139722,Dm:121258,Em:107598,Fm:127991,Gm:96639,Hm:107536,Im:130169,Jm:96661,Km:145188,Lm:96658,Mm:116646,Nm:121122,Om:96660,Pm:127738,Qm:127083,Rm:147842,Sm:104443,Tm:96659,Um:147595,Vm:106442,Wm:134840,
Xm:63667,Ym:63668,Zm:63669,an:130686,bn:147036,cn:78314,dn:147799,en:55761,fn:127098,gn:134841,hn:96368,jn:67374,kn:48992,ln:146176,mn:49956,nn:31961,pn:26388,qn:23811,rn:5E4,sn:126250,tn:96370,un:47355,vn:47356,wn:37935,xn:45521,yn:21760,zn:83769,An:49977,Bn:49974,Cn:93497,Dn:93498,En:34325,Fn:140759,Gn:115803,Hn:123707,In:100081,Jn:35309,Kn:68314,Ln:25602,Mn:100339,Nn:143516,On:59018,Pn:18248,Qn:50625,Rn:9729,Sn:37168,Tn:37169,Un:21667,Vn:16749,Wn:18635,Xn:39305,Yn:18046,Zn:53969,ao:8213,bo:93926,
co:102852,eo:110099,fo:22678,ho:69076,jo:137575,lo:139224,mo:100856,no:17736,oo:3832,po:147111,qo:55759,ro:64031,xo:93044,yo:93045,zo:34388,Ao:17657,Bo:17655,Co:39579,Do:39578,Eo:77448,Fo:8196,Go:11357,Ho:69877,Io:8197,Jo:82039};function lq(){var a=vb(mq),b;return dg(new Xf(function(c,d){a.onSuccess=function(e){yi(e)?c(new nq(e)):d(new oq("Request failed, status="+(e&&"status"in e?e.status:-1),"net.badstatus",e))};
a.onError=function(e){d(new oq("Unknown request error","net.unknown",e))};
a.onTimeout=function(e){d(new oq("Request timed out","net.timeout",e))};
b=aj("//googleads.g.doubleclick.net/pagead/id",a)}),function(c){c instanceof eg&&b.abort();
return bg(c)})}
function oq(a,b,c){ab.call(this,a+", errorCode="+b);this.errorCode=b;this.xhr=c;this.name="PromiseAjaxError"}
r(oq,ab);function nq(a){this.xhr=a}
;function pq(){this.i=0;this.h=null}
pq.prototype.then=function(a,b,c){return 1===this.i&&a?(a=a.call(c,this.h),Wf(a)?a:qq(a)):2===this.i&&b?(a=b.call(c,this.h),Wf(a)?a:rq(a)):this};
pq.prototype.getValue=function(){return this.h};
pq.prototype.$goog_Thenable=!0;function rq(a){var b=new pq;a=void 0===a?null:a;b.i=2;b.h=void 0===a?null:a;return b}
function qq(a){var b=new pq;a=void 0===a?null:a;b.i=1;b.h=void 0===a?null:a;return b}
;function sq(){if(le()||ak&&bk("applewebkit")&&!bk("version")&&(!bk("safari")||bk("gsa/"))||wc&&bk("version/"))return!0;if(M("enable_web_eom_visitor_data"))return A("EOM_VISITOR_DATA")?!1:!0;var a=A("INNERTUBE_CLIENT_NAME");return!a||"WEB"!==a&&"MWEB"!==a?!0:(a=mj("CONSENT"))?a.startsWith("YES+"):!0}
;function tq(a){ab.call(this,a.message||a.description||a.name);this.isMissing=a instanceof uq;this.isTimeout=a instanceof oq&&"net.timeout"==a.errorCode;this.isCanceled=a instanceof eg}
r(tq,ab);tq.prototype.name="BiscottiError";function uq(){ab.call(this,"Biscotti ID is missing from server")}
r(uq,ab);uq.prototype.name="BiscottiMissingError";var mq={format:"RAW",method:"GET",timeout:5E3,withCredentials:!0},vq=null;function ii(){if(M("disable_biscotti_fetch_entirely_for_all_web_clients"))return bg(Error("Biscotti id fetching has been disabled entirely."));if(!sq())return bg(Error("User has not consented - not fetching biscotti id."));if("1"==tb())return bg(Error("Biscotti ID is not available in private embed mode"));vq||(vq=dg(lq().then(wq),function(a){return xq(2,a)}));
return vq}
function wq(a){a=a.xhr.responseText;if(0!=a.lastIndexOf(")]}'",0))throw new uq;a=JSON.parse(a.substr(4));if(1<(a.type||1))throw new uq;a=a.id;ji(a);vq=qq(a);yq(18E5,2);return a}
function xq(a,b){b=new tq(b);ji("");vq=rq(b);0<a&&yq(12E4,a-1);throw b;}
function yq(a,b){zi(function(){dg(lq().then(wq,function(c){return xq(b,c)}),cb)},a)}
function zq(){try{var a=z("yt.ads.biscotti.getId_");return a?a():ii()}catch(b){return bg(b)}}
;function Aq(a){if("1"!=tb()){a&&hi();try{zq().then(function(){},function(){}),zi(Aq,18E5)}catch(b){fi(b)}}}
;function Bq(){this.yc=!0}
function Cq(a){var b={},c=ne([]);c&&(b.Authorization=c,c=a=null==a?void 0:a.sessionIndex,void 0===c&&(c=Number(A("SESSION_INDEX",0)),c=isNaN(c)?0:c),M("voice_search_auth_header_removal")||(b["X-Goog-AuthUser"]=c),"INNERTUBE_HOST_OVERRIDE"in Qh||(b["X-Origin"]=window.location.origin),void 0===a&&"DELEGATED_SESSION_ID"in Qh&&(b["X-Goog-PageId"]=A("DELEGATED_SESSION_ID")));return b}
;var Dq=Symbol("injectionDeps");function Eq(a){this.name=a}
Eq.prototype.toString=function(){return"InjectionToken("+this.name+")"};
function Fq(){this.key=Gq}
function Hq(){this.providers=new Map;this.h=new Map}
Hq.prototype.resolve=function(a){return a instanceof Fq?Iq(this,a.key,[],!0):Iq(this,a,[])};
function Iq(a,b,c,d){d=void 0===d?!1:d;if(-1<c.indexOf(b))throw Error("Deps cycle for: "+b);if(a.h.has(b))return a.h.get(b);if(!a.providers.has(b)){if(d)return;throw Error("No provider for: "+b);}d=a.providers.get(b);c.push(b);if(d.Cc)var e=d.Cc;else if(d.Bc)e=d[Dq]?Jq(a,d[Dq],c):[],e=d.Bc.apply(d,fa(e));else if(d.Jb){e=d.Jb;var f=e[Dq]?Jq(a,e[Dq],c):[];e=new (Function.prototype.bind.apply(e,[null].concat(fa(f))))}else throw Error("Could not resolve providers for: "+b);c.pop();d.Zo||a.h.set(b,e);
return e}
function Jq(a,b,c){return b?b.map(function(d){return d instanceof Fq?Iq(a,d.key,c,!0):Iq(a,d,c)}):[]}
;var Kq;var Lq={identityType:"UNAUTHENTICATED_IDENTITY_TYPE_UNKNOWN"};var Mq=new Map([["dark","USER_INTERFACE_THEME_DARK"],["light","USER_INTERFACE_THEME_LIGHT"]]);function Nq(){var a=void 0===a?window.location.href:a;if(M("kevlar_disable_theme_param"))return null;bc(cc(5,a));try{var b=ri(a).theme;return Mq.get(b)||null}catch(c){}return null}
;function Oq(){this.h={};if(this.i=nj()){var a=mj("CONSISTENCY");a&&Pq(this,{encryptedTokenJarContents:a})}}
Oq.prototype.handleResponse=function(a,b){var c,d;b=(null==(c=b.ba.context)?void 0:null==(d=c.request)?void 0:d.consistencyTokenJars)||[];var e;if(a=null==(e=a.responseContext)?void 0:e.consistencyTokenJar){e=p(b);for(c=e.next();!c.done;c=e.next())delete this.h[c.value.encryptedTokenJarContents];Pq(this,a)}};
function Pq(a,b){if(b.encryptedTokenJarContents&&(a.h[b.encryptedTokenJarContents]=b,"string"===typeof b.expirationSeconds)){var c=Number(b.expirationSeconds);setTimeout(function(){delete a.h[b.encryptedTokenJarContents]},1E3*c);
a.i&&lj("CONSISTENCY",b.encryptedTokenJarContents,c,void 0,!0)}}
;var Qq=window.location.hostname.split(".").slice(-2).join(".");function Rq(){var a=A("LOCATION_PLAYABILITY_TOKEN");"TVHTML5"===A("INNERTUBE_CLIENT_NAME")&&(this.h=Sq(this))&&(a=this.h.get("yt-location-playability-token"));a&&(this.locationPlayabilityToken=a,this.i=void 0)}
var Tq;Rq.getInstance=function(){Tq=z("yt.clientLocationService.instance");Tq||(Tq=new Rq,y("yt.clientLocationService.instance",Tq));return Tq};
Rq.prototype.setLocationOnInnerTubeContext=function(a){a.client||(a.client={});this.i?(a.client.locationInfo||(a.client.locationInfo={}),a.client.locationInfo.latitudeE7=1E7*this.i.coords.latitude,a.client.locationInfo.longitudeE7=1E7*this.i.coords.longitude,a.client.locationInfo.horizontalAccuracyMeters=Math.round(this.i.coords.accuracy),a.client.locationInfo.forceLocationPlayabilityTokenRefresh=!0):this.locationPlayabilityToken&&(a.client.locationPlayabilityToken=this.locationPlayabilityToken)};
Rq.prototype.handleResponse=function(a){var b;a=null==(b=a.responseContext)?void 0:b.locationPlayabilityToken;void 0!==a&&(this.locationPlayabilityToken=a,this.i=void 0,"TVHTML5"===A("INNERTUBE_CLIENT_NAME")?(this.h=Sq(this))&&this.h.set("yt-location-playability-token",a,15552E3):lj("YT_CL",JSON.stringify({loctok:a}),15552E3,Qq,!0))};
function Sq(a){return void 0===a.h?new Lj("yt-client-location"):a.h}
Rq.prototype.getCurrentPositionFromGeolocation=function(){var a=this;if(!(navigator&&navigator.geolocation&&navigator.geolocation.getCurrentPosition)||!M("web_enable_browser_geolocation_api")&&!M("enable_handoff_location_2fa_on_mweb"))return Promise.reject(Error("Geolocation unsupported"));var b=!1,c=1E4;M("enable_handoff_location_2fa_on_mweb")&&(b=!0,c=15E3);return new Promise(function(d,e){navigator.geolocation.getCurrentPosition(function(f){a.i=f;d(f)},function(f){e(f)},{enableHighAccuracy:b,
maximumAge:0,timeout:c})})};
Rq.prototype.createUnpluggedLocationInfo=function(a){var b={};a=a.coords;if(null==a?0:a.latitude)b.latitudeE7=Math.floor(1E7*a.latitude);if(null==a?0:a.longitude)b.longitudeE7=Math.floor(1E7*a.longitude);if(null==a?0:a.accuracy)b.locationRadiusMeters=Math.round(a.accuracy);return b};function Uq(a,b){var c;if((null==(c=a.signalServiceEndpoint)?0:c.signal)&&b.za&&(c=b.za[a.signalServiceEndpoint.signal]))return c();var d;if((null==(d=a.continuationCommand)?0:d.request)&&b.Qb&&(d=b.Qb[a.continuationCommand.request]))return d();for(var e in a)if(b.ob[e]&&(a=b.ob[e]))return a()}
;function Vq(a){return function(){return new a}}
;var Wq={},Xq=(Wq.WEB_UNPLUGGED="^unplugged/",Wq.WEB_UNPLUGGED_ONBOARDING="^unplugged/",Wq.WEB_UNPLUGGED_OPS="^unplugged/",Wq.WEB_UNPLUGGED_PUBLIC="^unplugged/",Wq.WEB_CREATOR="^creator/",Wq.WEB_KIDS="^kids/",Wq.WEB_EXPERIMENTS="^experiments/",Wq.WEB_MUSIC="^music/",Wq.WEB_REMIX="^music/",Wq.WEB_MUSIC_EMBEDDED_PLAYER="^music/",Wq.WEB_MUSIC_EMBEDDED_PLAYER="^main_app/|^sfv/",Wq);
function Yq(a){var b=void 0===b?"UNKNOWN_INTERFACE":b;if(1===a.length)return a[0];var c=Xq[b];if(c){var d=new RegExp(c),e=p(a);for(c=e.next();!c.done;c=e.next())if(c=c.value,d.exec(c))return c}var f=[];Object.entries(Xq).forEach(function(g){var h=p(g);g=h.next().value;h=h.next().value;b!==g&&f.push(h)});
d=new RegExp(f.join("|"));a.sort(function(g,h){return g.length-h.length});
e=p(a);for(c=e.next();!c.done;c=e.next())if(c=c.value,!d.exec(c))return c;return a[0]}
;function Zq(a,b){return{method:void 0===b?"POST":b,mode:ti(a)?"same-origin":"cors",credentials:ti(a)?"same-origin":"include"}}
;function $q(){}
$q.prototype.o=function(a,b,c){b=void 0===b?{}:b;c=void 0===c?Lq:c;var d=a.clickTrackingParams,e=this.l,f=!1;f=void 0===f?!1:f;e=void 0===e?!1:e;var g=A("INNERTUBE_CONTEXT");if(g){g=wb(g);M("web_no_tracking_params_in_shell_killswitch")||delete g.clickTracking;g.client||(g.client={});var h=g.client;"MWEB"===h.clientName&&(h.clientFormFactor=A("IS_TABLET")?"LARGE_FORM_FACTOR":"SMALL_FORM_FACTOR");h.screenWidthPoints=window.innerWidth;h.screenHeightPoints=window.innerHeight;h.screenPixelDensity=Math.round(window.devicePixelRatio||
1);h.screenDensityFloat=window.devicePixelRatio||1;h.utcOffsetMinutes=-Math.floor((new Date).getTimezoneOffset());var k=void 0===k?!1:k;pj.getInstance();var m="USER_INTERFACE_THEME_LIGHT";sj(165)?m="USER_INTERFACE_THEME_DARK":sj(174)?m="USER_INTERFACE_THEME_LIGHT":!M("kevlar_legacy_browsers")&&window.matchMedia&&window.matchMedia("(prefers-color-scheme)").matches&&window.matchMedia("(prefers-color-scheme: dark)").matches&&(m="USER_INTERFACE_THEME_DARK");k=k?m:Nq()||m;h.userInterfaceTheme=k;if(!f){if(k=
zj())h.connectionType=k;M("web_log_effective_connection_type")&&(k=Aj())&&(g.client.effectiveConnectionType=k)}var q;if(M("web_log_memory_total_kbytes")&&(null==(q=x.navigator)?0:q.deviceMemory)){var u;q=null==(u=x.navigator)?void 0:u.deviceMemory;g.client.memoryTotalKbytes=""+1E6*q}u=ri(x.location.href);!M("web_populate_internal_geo_killswitch")&&u.internalcountrycode&&(h.internalGeo=u.internalcountrycode);"MWEB"===h.clientName||"WEB"===h.clientName?(h.mainAppWebInfo={graftUrl:x.location.href},M("kevlar_woffle")&&
ij.h&&(h.mainAppWebInfo.pwaInstallabilityStatus=ij.h.h?"PWA_INSTALLABILITY_STATUS_CAN_BE_INSTALLED":"PWA_INSTALLABILITY_STATUS_UNKNOWN"),h.mainAppWebInfo.webDisplayMode=jj(),h.mainAppWebInfo.isWebNativeShareAvailable=navigator&&void 0!==navigator.share):"TVHTML5"===h.clientName&&(!M("web_lr_app_quality_killswitch")&&(u=A("LIVING_ROOM_APP_QUALITY"))&&(h.tvAppInfo=Object.assign(h.tvAppInfo||{},{appQuality:u})),u=A("LIVING_ROOM_CERTIFICATION_SCOPE"))&&(h.tvAppInfo=Object.assign(h.tvAppInfo||{},{certificationScope:u}));
if(!M("web_populate_time_zone_itc_killswitch")){b:{if("undefined"!==typeof Intl)try{var C=(new Intl.DateTimeFormat).resolvedOptions().timeZone;break b}catch(Oa){}C=void 0}C&&(h.timeZone=C)}(C=ai())?h.experimentsToken=C:delete h.experimentsToken;C=bi();Oq.h||(Oq.h=new Oq);h=Oq.h.h;u=[];q=0;for(var v in h)u[q++]=h[v];g.request=Object.assign({},g.request,{internalExperimentFlags:C,consistencyTokenJars:u});!M("web_prequest_context_killswitch")&&(v=A("INNERTUBE_CONTEXT_PREQUEST_CONTEXT"))&&(g.request.externalPrequestContext=
v);C=pj.getInstance();v=sj(58);C=C.get("gsml","");g.user=Object.assign({},g.user);v&&(g.user.enableSafetyMode=v);C&&(g.user.lockedSafetyMode=!0);M("warm_op_csn_cleanup")?e&&(f=eq())&&(g.clientScreenNonce=f):!f&&(f=eq())&&(g.clientScreenNonce=f);d&&(g.clickTracking={clickTrackingParams:d});if(d=z("yt.mdx.remote.remoteClient_"))g.remoteClient=d;M("web_enable_client_location_service")&&Rq.getInstance().setLocationOnInnerTubeContext(g);try{var E=ui(),F=E.bid;delete E.bid;g.adSignalsInfo={params:[],bid:F};
var I=p(Object.entries(E));for(var R=I.next();!R.done;R=I.next()){var O=p(R.value),S=O.next().value,ka=O.next().value;E=S;F=ka;d=void 0;null==(d=g.adSignalsInfo.params)||d.push({key:E,value:""+F})}}catch(Oa){Mp(Oa)}I=g}else Mp(Error("Error: No InnerTubeContext shell provided in ytconfig.")),I={};I={context:I};if(R=this.h(a)){this.i(I,R,b);var N;b="/youtubei/v1/"+Yq(this.j());var Ca;(a=null==(N=a.commandMetadata)?void 0:null==(Ca=N.webCommandMetadata)?void 0:Ca.apiUrl)&&(b=a);N=b;(Ca=A("INNERTUBE_HOST_OVERRIDE"))&&
(N=String(Ca)+String(ec(N)));Ca={};Ca.key=A("INNERTUBE_API_KEY");M("json_condensed_response")&&(Ca.prettyPrint="false");N=si(N,Ca||{},!1);N={input:N,ra:Zq(N),ba:I,config:Object.assign({},void 0)};N.config.Ga?N.config.Ga.identity=c:N.config.Ga={identity:c};return N}Mp(new Q("Error: Failed to create Request from Command.",a))};
da.Object.defineProperties($q.prototype,{l:{configurable:!0,enumerable:!0,get:function(){return!1}}});function ar(){}
r(ar,$q);ar.prototype.o=function(){return{input:"/getDatasyncIdsEndpoint",ra:Zq("/getDatasyncIdsEndpoint","GET"),ba:{}}};
ar.prototype.j=function(){return[]};
ar.prototype.h=function(){};
ar.prototype.i=function(){};var br={},cr=(br.GET_DATASYNC_IDS=Vq(ar),br);function dr(a){var b=Ja.apply(1,arguments);if(!er(a)||b.some(function(e){return!er(e)}))throw Error("Only objects may be merged.");
var c=a;b=p(b);for(var d=b.next();!d.done;d=b.next())fr(c,d.value);return c}
function fr(a,b){for(var c in b)if(er(b[c])){if(c in a&&!er(a[c]))throw Error("Cannot merge an object into a non-object.");c in a||(a[c]={});fr(a[c],b[c])}else if(gr(b[c])){if(c in a&&!gr(a[c]))throw Error("Cannot merge an array into a non-array.");c in a||(a[c]=[]);hr(a[c],b[c])}else a[c]=b[c];return a}
function hr(a,b){b=p(b);for(var c=b.next();!c.done;c=b.next())c=c.value,er(c)?a.push(fr({},c)):gr(c)?a.push(hr([],c)):a.push(c);return a}
function er(a){return"object"===typeof a&&!Array.isArray(a)}
function gr(a){return"object"===typeof a&&Array.isArray(a)}
;function ir(a,b){Ql.call(this,1,arguments);this.timer=b}
r(ir,Ql);var jr=new Rl("aft-recorded",ir);var kr=window;function lr(){this.timing={};this.clearResourceTimings=function(){};
this.webkitClearResourceTimings=function(){};
this.mozClearResourceTimings=function(){};
this.msClearResourceTimings=function(){};
this.oClearResourceTimings=function(){}}
var T=kr.performance||kr.mozPerformance||kr.msPerformance||kr.webkitPerformance||new lr;var mr=!1,nr={'script[name="scheduler/scheduler"]':"sj",'script[name="player/base"]':"pj",'link[rel="stylesheet"][name="www-player"]':"pc",'link[rel="stylesheet"][name="player/www-player"]':"pc",'script[name="desktop_polymer/desktop_polymer"]':"dpj",'link[rel="import"][name="desktop_polymer"]':"dph",'script[name="mobile-c3"]':"mcj",'link[rel="stylesheet"][name="mobile-c3"]':"mcc",'script[name="player-plasma-ias-phone/base"]':"mcppj",'script[name="player-plasma-ias-tablet/base"]':"mcptj",'link[rel="stylesheet"][name="mobile-polymer-player-ias"]':"mcpc",
'link[rel="stylesheet"][name="mobile-polymer-player-svg-ias"]':"mcpsc",'script[name="mobile_blazer_core_mod"]':"mbcj",'link[rel="stylesheet"][name="mobile_blazer_css"]':"mbc",'script[name="mobile_blazer_logged_in_users_mod"]':"mbliuj",'script[name="mobile_blazer_logged_out_users_mod"]':"mblouj",'script[name="mobile_blazer_noncore_mod"]':"mbnj","#player_css":"mbpc",'script[name="mobile_blazer_desktopplayer_mod"]':"mbpj",'link[rel="stylesheet"][name="mobile_blazer_tablet_css"]':"mbtc",'script[name="mobile_blazer_watch_mod"]':"mbwj"};
Xa(T.clearResourceTimings||T.webkitClearResourceTimings||T.mozClearResourceTimings||T.msClearResourceTimings||T.oClearResourceTimings||cb,T);function or(a){var b=pr(a);if(b.aft)return b.aft;a=A((a||"")+"TIMING_AFT_KEYS",["ol"]);for(var c=a.length,d=0;d<c;d++){var e=b[a[d]];if(e)return e}return NaN}
function qr(){var a;if(M("csi_use_performance_navigation_timing")){var b,c,d,e=null==T?void 0:null==(a=T.getEntriesByType)?void 0:null==(b=a.call(T,"navigation"))?void 0:null==(c=b[0])?void 0:null==(d=c.toJSON)?void 0:d.call(c);e?(e.requestStart=rr(e.requestStart),e.responseEnd=rr(e.responseEnd),e.redirectStart=rr(e.redirectStart),e.redirectEnd=rr(e.redirectEnd),e.domainLookupEnd=rr(e.domainLookupEnd),e.connectStart=rr(e.connectStart),e.connectEnd=rr(e.connectEnd),e.responseStart=rr(e.responseStart),
e.secureConnectionStart=rr(e.secureConnectionStart),e.domainLookupStart=rr(e.domainLookupStart),e.isPerformanceNavigationTiming=!0,a=e):a=T.timing}else a=T.timing;return a}
function sr(){return M("csi_use_time_origin")&&T.timeOrigin?Math.floor(T.timeOrigin):T.timing.navigationStart}
function rr(a){return Math.round(sr()+a)}
function tr(a){var b;(b=z("ytcsi."+(a||"")+"data_"))||(b={tick:{},info:{}},y("ytcsi."+(a||"")+"data_",b));return b}
function ur(a){a=tr(a);a.info||(a.info={});return a.info}
function pr(a){a=tr(a);a.tick||(a.tick={});return a.tick}
function vr(a){a=tr(a);if(a.gel){var b=a.gel;b.gelInfos||(b.gelInfos={});b.gelTicks||(b.gelTicks={})}else a.gel={gelTicks:{},gelInfos:{}};return a.gel}
function wr(a){a=vr(a);a.gelInfos||(a.gelInfos={});return a.gelInfos}
function xr(a){var b=tr(a).nonce;b||(b=Up(),tr(a).nonce=b);return b}
function yr(a){var b=pr(a||""),c=or(a);c&&!mr&&(Wl(jr,new ir(Math.round(c-b._start),a)),mr=!0)}
function zr(a,b){for(var c=p(Object.keys(b)),d=c.next();!d.done;d=c.next())if(d=d.value,!Object.keys(a).includes(d)||"object"===typeof b[d]&&!zr(a[d],b[d]))return!1;return!0}
;function Ar(){if(T.getEntriesByType){var a=T.getEntriesByType("paint");if(a=jb(a,function(b){return"first-paint"===b.name}))return rr(a.startTime)}a=T.timing;
return a.cc?Math.max(0,a.cc):0}
;function Br(){var a=z("ytcsi.debug");a||(a=[],y("ytcsi.debug",a),y("ytcsi.reference",{}));return a}
function Cr(a){a=a||"";var b=z("ytcsi.reference");b||(Br(),b=z("ytcsi.reference"));if(b[a])return b[a];var c=Br(),d={timerName:a,info:{},tick:{},span:{},jspbInfo:[]};c.push(d);return b[a]=d}
;var U={},Dr=(U.auto_search="LATENCY_ACTION_AUTO_SEARCH",U.ad_to_ad="LATENCY_ACTION_AD_TO_AD",U.ad_to_video="LATENCY_ACTION_AD_TO_VIDEO",U["analytics.explore"]="LATENCY_ACTION_CREATOR_ANALYTICS_EXPLORE",U.app_startup="LATENCY_ACTION_APP_STARTUP",U["artist.analytics"]="LATENCY_ACTION_CREATOR_ARTIST_ANALYTICS",U["artist.events"]="LATENCY_ACTION_CREATOR_ARTIST_CONCERTS",U["artist.presskit"]="LATENCY_ACTION_CREATOR_ARTIST_PROFILE",U.browse="LATENCY_ACTION_BROWSE",U.cast_splash="LATENCY_ACTION_CAST_SPLASH",
U.channels="LATENCY_ACTION_CHANNELS",U.creator_channel_dashboard="LATENCY_ACTION_CREATOR_CHANNEL_DASHBOARD",U["channel.analytics"]="LATENCY_ACTION_CREATOR_CHANNEL_ANALYTICS",U["channel.comments"]="LATENCY_ACTION_CREATOR_CHANNEL_COMMENTS",U["channel.content"]="LATENCY_ACTION_CREATOR_POST_LIST",U["channel.copyright"]="LATENCY_ACTION_CREATOR_CHANNEL_COPYRIGHT",U["channel.editing"]="LATENCY_ACTION_CREATOR_CHANNEL_EDITING",U["channel.monetization"]="LATENCY_ACTION_CREATOR_CHANNEL_MONETIZATION",U["channel.music"]=
"LATENCY_ACTION_CREATOR_CHANNEL_MUSIC",U["channel.playlists"]="LATENCY_ACTION_CREATOR_CHANNEL_PLAYLISTS",U["channel.translations"]="LATENCY_ACTION_CREATOR_CHANNEL_TRANSLATIONS",U["channel.videos"]="LATENCY_ACTION_CREATOR_CHANNEL_VIDEOS",U["channel.live_streaming"]="LATENCY_ACTION_CREATOR_LIVE_STREAMING",U.chips="LATENCY_ACTION_CHIPS",U["dialog.copyright_strikes"]="LATENCY_ACTION_CREATOR_DIALOG_COPYRIGHT_STRIKES",U["dialog.uploads"]="LATENCY_ACTION_CREATOR_DIALOG_UPLOADS",U.direct_playback="LATENCY_ACTION_DIRECT_PLAYBACK",
U.embed="LATENCY_ACTION_EMBED",U.entity_key_serialization_perf="LATENCY_ACTION_ENTITY_KEY_SERIALIZATION_PERF",U.entity_key_deserialization_perf="LATENCY_ACTION_ENTITY_KEY_DESERIALIZATION_PERF",U.explore="LATENCY_ACTION_EXPLORE",U.home="LATENCY_ACTION_HOME",U.library="LATENCY_ACTION_LIBRARY",U.live="LATENCY_ACTION_LIVE",U.live_pagination="LATENCY_ACTION_LIVE_PAGINATION",U.onboarding="LATENCY_ACTION_ONBOARDING",U.parent_profile_settings="LATENCY_ACTION_KIDS_PARENT_PROFILE_SETTINGS",U.parent_tools_collection=
"LATENCY_ACTION_PARENT_TOOLS_COLLECTION",U.parent_tools_dashboard="LATENCY_ACTION_PARENT_TOOLS_DASHBOARD",U.player_att="LATENCY_ACTION_PLAYER_ATTESTATION",U["post.comments"]="LATENCY_ACTION_CREATOR_POST_COMMENTS",U["post.edit"]="LATENCY_ACTION_CREATOR_POST_EDIT",U.prebuffer="LATENCY_ACTION_PREBUFFER",U.prefetch="LATENCY_ACTION_PREFETCH",U.profile_settings="LATENCY_ACTION_KIDS_PROFILE_SETTINGS",U.profile_switcher="LATENCY_ACTION_LOGIN",U.reel_watch="LATENCY_ACTION_REEL_WATCH",U.results="LATENCY_ACTION_RESULTS",
U.search_ui="LATENCY_ACTION_SEARCH_UI",U.search_suggest="LATENCY_ACTION_SUGGEST",U.search_zero_state="LATENCY_ACTION_SEARCH_ZERO_STATE",U.secret_code="LATENCY_ACTION_KIDS_SECRET_CODE",U.seek="LATENCY_ACTION_PLAYER_SEEK",U.settings="LATENCY_ACTION_SETTINGS",U.tenx="LATENCY_ACTION_TENX",U.video_to_ad="LATENCY_ACTION_VIDEO_TO_AD",U.watch="LATENCY_ACTION_WATCH",U.watch_it_again="LATENCY_ACTION_KIDS_WATCH_IT_AGAIN",U["watch,watch7"]="LATENCY_ACTION_WATCH",U["watch,watch7_html5"]="LATENCY_ACTION_WATCH",
U["watch,watch7ad"]="LATENCY_ACTION_WATCH",U["watch,watch7ad_html5"]="LATENCY_ACTION_WATCH",U.wn_comments="LATENCY_ACTION_LOAD_COMMENTS",U.ww_rqs="LATENCY_ACTION_WHO_IS_WATCHING",U["video.analytics"]="LATENCY_ACTION_CREATOR_VIDEO_ANALYTICS",U["video.comments"]="LATENCY_ACTION_CREATOR_VIDEO_COMMENTS",U["video.edit"]="LATENCY_ACTION_CREATOR_VIDEO_EDIT",U["video.editor"]="LATENCY_ACTION_CREATOR_VIDEO_VIDEO_EDITOR",U["video.editor_async"]="LATENCY_ACTION_CREATOR_VIDEO_VIDEO_EDITOR_ASYNC",U["video.live_settings"]=
"LATENCY_ACTION_CREATOR_VIDEO_LIVE_SETTINGS",U["video.live_streaming"]="LATENCY_ACTION_CREATOR_VIDEO_LIVE_STREAMING",U["video.monetization"]="LATENCY_ACTION_CREATOR_VIDEO_MONETIZATION",U["video.translations"]="LATENCY_ACTION_CREATOR_VIDEO_TRANSLATIONS",U.voice_assistant="LATENCY_ACTION_VOICE_ASSISTANT",U.cast_load_by_entity_to_watch="LATENCY_ACTION_CAST_LOAD_BY_ENTITY_TO_WATCH",U.networkless_performance="LATENCY_ACTION_NETWORKLESS_PERFORMANCE",U),V={},Er=(V.ad_allowed="adTypesAllowed",V.yt_abt="adBreakType",
V.ad_cpn="adClientPlaybackNonce",V.ad_docid="adVideoId",V.yt_ad_an="adNetworks",V.ad_at="adType",V.aida="appInstallDataAgeMs",V.browse_id="browseId",V.p="httpProtocol",V.t="transportProtocol",V.cs="commandSource",V.cpn="clientPlaybackNonce",V.ccs="creatorInfo.creatorCanaryState",V.ctop="creatorInfo.topEntityType",V.csn="clientScreenNonce",V.docid="videoId",V.GetHome_rid="requestIds",V.GetSearch_rid="requestIds",V.GetPlayer_rid="requestIds",V.GetWatchNext_rid="requestIds",V.GetBrowse_rid="requestIds",
V.GetLibrary_rid="requestIds",V.is_continuation="isContinuation",V.is_nav="isNavigation",V.b_p="kabukiInfo.browseParams",V.is_prefetch="kabukiInfo.isPrefetch",V.is_secondary_nav="kabukiInfo.isSecondaryNav",V.nav_type="kabukiInfo.navigationType",V.prev_browse_id="kabukiInfo.prevBrowseId",V.query_source="kabukiInfo.querySource",V.voz_type="kabukiInfo.vozType",V.yt_lt="loadType",V.mver="creatorInfo.measurementVersion",V.yt_ad="isMonetized",V.nr="webInfo.navigationReason",V.nrsu="navigationRequestedSameUrl",
V.pnt="performanceNavigationTiming",V.prt="playbackRequiresTap",V.plt="playerInfo.playbackType",V.pis="playerInfo.playerInitializedState",V.paused="playerInfo.isPausedOnLoad",V.yt_pt="playerType",V.fmt="playerInfo.itag",V.yt_pl="watchInfo.isPlaylist",V.yt_pre="playerInfo.preloadType",V.yt_ad_pr="prerollAllowed",V.pa="previousAction",V.yt_red="isRedSubscriber",V.rce="mwebInfo.responseContentEncoding",V.rc="resourceInfo.resourceCache",V.scrh="screenHeight",V.scrw="screenWidth",V.st="serverTimeMs",V.ssdm=
"shellStartupDurationMs",V.br_trs="tvInfo.bedrockTriggerState",V.kebqat="kabukiInfo.earlyBrowseRequestInfo.abandonmentType",V.kebqa="kabukiInfo.earlyBrowseRequestInfo.adopted",V.label="tvInfo.label",V.is_mdx="tvInfo.isMdx",V.preloaded="tvInfo.isPreloaded",V.aac_type="tvInfo.authAccessCredentialType",V.upg_player_vis="playerInfo.visibilityState",V.query="unpluggedInfo.query",V.upg_chip_ids_string="unpluggedInfo.upgChipIdsString",V.yt_vst="videoStreamType",V.vph="viewportHeight",V.vpw="viewportWidth",
V.yt_vis="isVisible",V.rcl="mwebInfo.responseContentLength",V.GetSettings_rid="requestIds",V.GetTrending_rid="requestIds",V.GetMusicSearchSuggestions_rid="requestIds",V.REQUEST_ID="requestIds",V),Fr="isContinuation isNavigation kabukiInfo.earlyBrowseRequestInfo.adopted kabukiInfo.isPrefetch kabukiInfo.isSecondaryNav isMonetized navigationRequestedSameUrl performanceNavigationTiming playerInfo.isPausedOnLoad prerollAllowed isRedSubscriber tvInfo.isMdx tvInfo.isPreloaded isVisible watchInfo.isPlaylist playbackRequiresTap".split(" "),
Gr={},Hr=(Gr.ccs="CANARY_STATE_",Gr.mver="MEASUREMENT_VERSION_",Gr.pis="PLAYER_INITIALIZED_STATE_",Gr.yt_pt="LATENCY_PLAYER_",Gr.pa="LATENCY_ACTION_",Gr.ctop="TOP_ENTITY_TYPE_",Gr.yt_vst="VIDEO_STREAM_TYPE_",Gr),Ir="all_vc ap aq c cbr cbrand cbrver cmodel cos cosver cplatform ctheme cver ei l_an l_mm plid srt yt_fss yt_li vpst vpni2 vpil2 icrc icrt pa GetAccountOverview_rid GetHistory_rid cmt d_vpct d_vpnfi d_vpni nsru pc pfa pfeh pftr pnc prerender psc rc start tcrt tcrc ssr vpr vps yt_abt yt_fn yt_fs yt_pft yt_pre yt_pt yt_pvis ytu_pvis yt_ref yt_sts tds".split(" ");
function Jr(a){return Dr[a]||"LATENCY_ACTION_UNKNOWN"}
function Kr(a,b,c){c=vr(c);if(c.gelInfos)c.gelInfos[a]=!0;else{var d={};c.gelInfos=(d[a]=!0,d)}if(a.match("_rid")){var e=a.split("_rid")[0];a="REQUEST_ID"}if(a in Er){c=Er[a];0<=eb(Fr,c)&&(b=!!b);a in Hr&&"string"===typeof b&&(b=Hr[a]+b.toUpperCase());a=b;b=c.split(".");for(var f=d={},g=0;g<b.length-1;g++){var h=b[g];f[h]={};f=f[h]}f[b[b.length-1]]="requestIds"===c?[{id:a,endpoint:e}]:a;return dr({},d)}0<=eb(Ir,a)||Np(new Q("Unknown label logged with GEL CSI",a))}
;var W={LATENCY_ACTION_KIDS_PROFILE_SWITCHER:90,LATENCY_ACTION_OFFLINE_THUMBNAIL_TRANSFER:100,LATENCY_ACTION_CREATOR_VIDEO_VIDEO_EDITOR_ASYNC:46,LATENCY_ACTION_CREATOR_VIDEO_VIDEO_EDITOR:37,LATENCY_ACTION_SPINNER_DISPLAYED:14,LATENCY_ACTION_PLAYABILITY_CHECK:10,LATENCY_ACTION_PROCESS:9,LATENCY_ACTION_APP_STARTUP:5,LATENCY_ACTION_THUMBNAIL_FETCH:156,LATENCY_ACTION_ABANDONED_DIRECT_PLAYBACK:154,LATENCY_ACTION_SHARE_VIDEO:153,LATENCY_ACTION_AD_TO_VIDEO_INT:152,LATENCY_ACTION_ABANDONED_BROWSE:151,LATENCY_ACTION_PLAYER_ROTATION:150,
LATENCY_ACTION_SHOPPING_IN_APP:124,LATENCY_ACTION_PLAYER_ATTESTATION:121,LATENCY_ACTION_PLAYER_SEEK:119,LATENCY_ACTION_SUPER_STICKER_BUY_FLOW:114,LATENCY_ACTION_BLOCKS_PERFORMANCE:148,LATENCY_ACTION_ASSISTANT_QUERY:138,LATENCY_ACTION_ASSISTANT_SETTINGS:137,LATENCY_ACTION_ENTITY_KEY_DESERIALIZATION_PERF:129,LATENCY_ACTION_ENTITY_KEY_SERIALIZATION_PERF:128,LATENCY_ACTION_PROOF_OF_ORIGIN_TOKEN_CREATE:127,LATENCY_ACTION_EMBEDS_SDK_INITIALIZATION:123,LATENCY_ACTION_NETWORKLESS_PERFORMANCE:122,LATENCY_ACTION_DOWNLOADS_EXPANSION:133,
LATENCY_ACTION_ENTITY_TRANSFORM:131,LATENCY_ACTION_DOWNLOADS_COMPATIBILITY_LAYER:96,LATENCY_ACTION_EMBEDS_SET_VIDEO:95,LATENCY_ACTION_SETTINGS:93,LATENCY_ACTION_ABANDONED_STARTUP:81,LATENCY_ACTION_MEDIA_BROWSER_ALARM_PLAY:80,LATENCY_ACTION_MEDIA_BROWSER_SEARCH:79,LATENCY_ACTION_MEDIA_BROWSER_LOAD_TREE:78,LATENCY_ACTION_WHO_IS_WATCHING:77,LATENCY_ACTION_CAST_LOAD_BY_ENTITY_TO_WATCH:76,LATENCY_ACTION_LITE_SWITCH_ACCOUNT:73,LATENCY_ACTION_ELEMENTS_PERFORMANCE:70,LATENCY_ACTION_LOCATION_SIGNAL_COLLECTION:69,
LATENCY_ACTION_MODIFY_CHANNEL_NOTIFICATION:65,LATENCY_ACTION_OFFLINE_STORE_START:61,LATENCY_ACTION_REEL_EDITOR:58,LATENCY_ACTION_CHANNEL_SUBSCRIBE:56,LATENCY_ACTION_CHANNEL_PREVIEW:55,LATENCY_ACTION_PREFETCH:52,LATENCY_ACTION_ABANDONED_WATCH:45,LATENCY_ACTION_LOAD_COMMENT_REPLIES:26,LATENCY_ACTION_LOAD_COMMENTS:25,LATENCY_ACTION_EDIT_COMMENT:24,LATENCY_ACTION_NEW_COMMENT:23,LATENCY_ACTION_OFFLINE_SHARING_RECEIVER_PAIRING:19,LATENCY_ACTION_EMBED:18,LATENCY_ACTION_MDX_LAUNCH:15,LATENCY_ACTION_RESOLVE_URL:13,
LATENCY_ACTION_CAST_SPLASH:149,LATENCY_ACTION_MDX_CAST:120,LATENCY_ACTION_MDX_COMMAND:12,LATENCY_ACTION_REEL_SELECT_SEGMENT:136,LATENCY_ACTION_ACCELERATED_EFFECTS:145,LATENCY_ACTION_UPLOAD_AUDIO_MIXER:147,LATENCY_ACTION_SHORTS_SEG_IMP_TRANSCODING:146,LATENCY_ACTION_SHORTS_AUDIO_PICKER_PLAYBACK:130,LATENCY_ACTION_SHORTS_WAVEFORM_DOWNLOAD:125,LATENCY_ACTION_SHORTS_VIDEO_INGESTION:155,LATENCY_ACTION_SHORTS_GALLERY:107,LATENCY_ACTION_SHORTS_TRIM:105,LATENCY_ACTION_SHORTS_EDIT:104,LATENCY_ACTION_SHORTS_CAMERA:103,
LATENCY_ACTION_PARENT_TOOLS_DASHBOARD:102,LATENCY_ACTION_PARENT_TOOLS_COLLECTION:101,LATENCY_ACTION_MUSIC_LOAD_RECOMMENDED_MEDIA_ITEMS:116,LATENCY_ACTION_MUSIC_LOAD_MEDIA_ITEMS:115,LATENCY_ACTION_MUSIC_ALBUM_DETAIL:72,LATENCY_ACTION_MUSIC_PLAYLIST_DETAIL:71,LATENCY_ACTION_CHIPS:68,LATENCY_ACTION_SEARCH_ZERO_STATE:67,LATENCY_ACTION_LIVE_PAGINATION:117,LATENCY_ACTION_LIVE:20,LATENCY_ACTION_PREBUFFER:40,LATENCY_ACTION_TENX:39,LATENCY_ACTION_KIDS_PROFILE_SETTINGS:94,LATENCY_ACTION_KIDS_WATCH_IT_AGAIN:92,
LATENCY_ACTION_KIDS_SECRET_CODE:91,LATENCY_ACTION_KIDS_PARENT_PROFILE_SETTINGS:89,LATENCY_ACTION_KIDS_ONBOARDING:88,LATENCY_ACTION_KIDS_VOICE_SEARCH:82,LATENCY_ACTION_KIDS_CURATED_COLLECTION:62,LATENCY_ACTION_KIDS_LIBRARY:53,LATENCY_ACTION_CREATOR_VIDEO_TRANSLATIONS:38,LATENCY_ACTION_CREATOR_VIDEO_MONETIZATION:74,LATENCY_ACTION_CREATOR_VIDEO_LIVE_STREAMING:141,LATENCY_ACTION_CREATOR_VIDEO_LIVE_SETTINGS:142,LATENCY_ACTION_CREATOR_VIDEO_EDITOR_ASYNC:51,LATENCY_ACTION_CREATOR_VIDEO_EDITOR:50,LATENCY_ACTION_CREATOR_VIDEO_EDIT:36,
LATENCY_ACTION_CREATOR_VIDEO_COMMENTS:34,LATENCY_ACTION_CREATOR_VIDEO_ANALYTICS:33,LATENCY_ACTION_CREATOR_POST_LIST:112,LATENCY_ACTION_CREATOR_POST_EDIT:110,LATENCY_ACTION_CREATOR_POST_COMMENTS:111,LATENCY_ACTION_CREATOR_LIVE_STREAMING:108,LATENCY_ACTION_CREATOR_DIALOG_UPLOADS:86,LATENCY_ACTION_CREATOR_DIALOG_COPYRIGHT_STRIKES:87,LATENCY_ACTION_CREATOR_CHANNEL_VIDEOS:32,LATENCY_ACTION_CREATOR_CHANNEL_TRANSLATIONS:48,LATENCY_ACTION_CREATOR_CHANNEL_PLAYLISTS:139,LATENCY_ACTION_CREATOR_CHANNEL_MUSIC:99,
LATENCY_ACTION_CREATOR_CHANNEL_MONETIZATION:43,LATENCY_ACTION_CREATOR_CHANNEL_EDITING:113,LATENCY_ACTION_CREATOR_CHANNEL_DASHBOARD:49,LATENCY_ACTION_CREATOR_CHANNEL_COPYRIGHT:44,LATENCY_ACTION_CREATOR_CHANNEL_COMMENTS:66,LATENCY_ACTION_CREATOR_CHANNEL_ANALYTICS:31,LATENCY_ACTION_CREATOR_ARTIST_PROFILE:85,LATENCY_ACTION_CREATOR_ARTIST_CONCERTS:84,LATENCY_ACTION_CREATOR_ARTIST_ANALYTICS:83,LATENCY_ACTION_CREATOR_ANALYTICS_EXPLORE:140,LATENCY_ACTION_STORYBOARD_THUMBNAILS:118,LATENCY_ACTION_SEARCH_THUMBNAILS:59,
LATENCY_ACTION_ON_DEVICE_MODEL_DOWNLOAD:54,LATENCY_ACTION_VOICE_ASSISTANT:47,LATENCY_ACTION_SEARCH_UI:35,LATENCY_ACTION_SUGGEST:30,LATENCY_ACTION_AUTO_SEARCH:126,LATENCY_ACTION_DOWNLOADS:98,LATENCY_ACTION_EXPLORE:75,LATENCY_ACTION_VIDEO_LIST:63,LATENCY_ACTION_HOME_RESUME:60,LATENCY_ACTION_SUBSCRIPTIONS_LIST:57,LATENCY_ACTION_THUMBNAIL_LOAD:42,LATENCY_ACTION_FIRST_THUMBNAIL_LOAD:29,LATENCY_ACTION_SUBSCRIPTIONS_FEED:109,LATENCY_ACTION_SUBSCRIPTIONS:28,LATENCY_ACTION_TRENDING:27,LATENCY_ACTION_LIBRARY:21,
LATENCY_ACTION_VIDEO_THUMBNAIL:8,LATENCY_ACTION_SHOW_MORE:7,LATENCY_ACTION_VIDEO_PREVIEW:6,LATENCY_ACTION_PREBUFFER_VIDEO:144,LATENCY_ACTION_PREFETCH_VIDEO:143,LATENCY_ACTION_DIRECT_PLAYBACK:132,LATENCY_ACTION_REEL_WATCH:41,LATENCY_ACTION_AD_TO_AD:22,LATENCY_ACTION_VIDEO_TO_AD:17,LATENCY_ACTION_AD_TO_VIDEO:16,LATENCY_ACTION_ONBOARDING:135,LATENCY_ACTION_LOGIN:97,LATENCY_ACTION_BROWSE:11,LATENCY_ACTION_CHANNELS:4,LATENCY_ACTION_WATCH:3,LATENCY_ACTION_RESULTS:2,LATENCY_ACTION_HOME:1,LATENCY_ACTION_STARTUP:106,
LATENCY_ACTION_UNKNOWN:0};W[W.LATENCY_ACTION_KIDS_PROFILE_SWITCHER]="LATENCY_ACTION_KIDS_PROFILE_SWITCHER";W[W.LATENCY_ACTION_OFFLINE_THUMBNAIL_TRANSFER]="LATENCY_ACTION_OFFLINE_THUMBNAIL_TRANSFER";W[W.LATENCY_ACTION_CREATOR_VIDEO_VIDEO_EDITOR_ASYNC]="LATENCY_ACTION_CREATOR_VIDEO_VIDEO_EDITOR_ASYNC";W[W.LATENCY_ACTION_CREATOR_VIDEO_VIDEO_EDITOR]="LATENCY_ACTION_CREATOR_VIDEO_VIDEO_EDITOR";W[W.LATENCY_ACTION_SPINNER_DISPLAYED]="LATENCY_ACTION_SPINNER_DISPLAYED";
W[W.LATENCY_ACTION_PLAYABILITY_CHECK]="LATENCY_ACTION_PLAYABILITY_CHECK";W[W.LATENCY_ACTION_PROCESS]="LATENCY_ACTION_PROCESS";W[W.LATENCY_ACTION_APP_STARTUP]="LATENCY_ACTION_APP_STARTUP";W[W.LATENCY_ACTION_THUMBNAIL_FETCH]="LATENCY_ACTION_THUMBNAIL_FETCH";W[W.LATENCY_ACTION_ABANDONED_DIRECT_PLAYBACK]="LATENCY_ACTION_ABANDONED_DIRECT_PLAYBACK";W[W.LATENCY_ACTION_SHARE_VIDEO]="LATENCY_ACTION_SHARE_VIDEO";W[W.LATENCY_ACTION_AD_TO_VIDEO_INT]="LATENCY_ACTION_AD_TO_VIDEO_INT";
W[W.LATENCY_ACTION_ABANDONED_BROWSE]="LATENCY_ACTION_ABANDONED_BROWSE";W[W.LATENCY_ACTION_PLAYER_ROTATION]="LATENCY_ACTION_PLAYER_ROTATION";W[W.LATENCY_ACTION_SHOPPING_IN_APP]="LATENCY_ACTION_SHOPPING_IN_APP";W[W.LATENCY_ACTION_PLAYER_ATTESTATION]="LATENCY_ACTION_PLAYER_ATTESTATION";W[W.LATENCY_ACTION_PLAYER_SEEK]="LATENCY_ACTION_PLAYER_SEEK";W[W.LATENCY_ACTION_SUPER_STICKER_BUY_FLOW]="LATENCY_ACTION_SUPER_STICKER_BUY_FLOW";W[W.LATENCY_ACTION_BLOCKS_PERFORMANCE]="LATENCY_ACTION_BLOCKS_PERFORMANCE";
W[W.LATENCY_ACTION_ASSISTANT_QUERY]="LATENCY_ACTION_ASSISTANT_QUERY";W[W.LATENCY_ACTION_ASSISTANT_SETTINGS]="LATENCY_ACTION_ASSISTANT_SETTINGS";W[W.LATENCY_ACTION_ENTITY_KEY_DESERIALIZATION_PERF]="LATENCY_ACTION_ENTITY_KEY_DESERIALIZATION_PERF";W[W.LATENCY_ACTION_ENTITY_KEY_SERIALIZATION_PERF]="LATENCY_ACTION_ENTITY_KEY_SERIALIZATION_PERF";W[W.LATENCY_ACTION_PROOF_OF_ORIGIN_TOKEN_CREATE]="LATENCY_ACTION_PROOF_OF_ORIGIN_TOKEN_CREATE";W[W.LATENCY_ACTION_EMBEDS_SDK_INITIALIZATION]="LATENCY_ACTION_EMBEDS_SDK_INITIALIZATION";
W[W.LATENCY_ACTION_NETWORKLESS_PERFORMANCE]="LATENCY_ACTION_NETWORKLESS_PERFORMANCE";W[W.LATENCY_ACTION_DOWNLOADS_EXPANSION]="LATENCY_ACTION_DOWNLOADS_EXPANSION";W[W.LATENCY_ACTION_ENTITY_TRANSFORM]="LATENCY_ACTION_ENTITY_TRANSFORM";W[W.LATENCY_ACTION_DOWNLOADS_COMPATIBILITY_LAYER]="LATENCY_ACTION_DOWNLOADS_COMPATIBILITY_LAYER";W[W.LATENCY_ACTION_EMBEDS_SET_VIDEO]="LATENCY_ACTION_EMBEDS_SET_VIDEO";W[W.LATENCY_ACTION_SETTINGS]="LATENCY_ACTION_SETTINGS";W[W.LATENCY_ACTION_ABANDONED_STARTUP]="LATENCY_ACTION_ABANDONED_STARTUP";
W[W.LATENCY_ACTION_MEDIA_BROWSER_ALARM_PLAY]="LATENCY_ACTION_MEDIA_BROWSER_ALARM_PLAY";W[W.LATENCY_ACTION_MEDIA_BROWSER_SEARCH]="LATENCY_ACTION_MEDIA_BROWSER_SEARCH";W[W.LATENCY_ACTION_MEDIA_BROWSER_LOAD_TREE]="LATENCY_ACTION_MEDIA_BROWSER_LOAD_TREE";W[W.LATENCY_ACTION_WHO_IS_WATCHING]="LATENCY_ACTION_WHO_IS_WATCHING";W[W.LATENCY_ACTION_CAST_LOAD_BY_ENTITY_TO_WATCH]="LATENCY_ACTION_CAST_LOAD_BY_ENTITY_TO_WATCH";W[W.LATENCY_ACTION_LITE_SWITCH_ACCOUNT]="LATENCY_ACTION_LITE_SWITCH_ACCOUNT";
W[W.LATENCY_ACTION_ELEMENTS_PERFORMANCE]="LATENCY_ACTION_ELEMENTS_PERFORMANCE";W[W.LATENCY_ACTION_LOCATION_SIGNAL_COLLECTION]="LATENCY_ACTION_LOCATION_SIGNAL_COLLECTION";W[W.LATENCY_ACTION_MODIFY_CHANNEL_NOTIFICATION]="LATENCY_ACTION_MODIFY_CHANNEL_NOTIFICATION";W[W.LATENCY_ACTION_OFFLINE_STORE_START]="LATENCY_ACTION_OFFLINE_STORE_START";W[W.LATENCY_ACTION_REEL_EDITOR]="LATENCY_ACTION_REEL_EDITOR";W[W.LATENCY_ACTION_CHANNEL_SUBSCRIBE]="LATENCY_ACTION_CHANNEL_SUBSCRIBE";
W[W.LATENCY_ACTION_CHANNEL_PREVIEW]="LATENCY_ACTION_CHANNEL_PREVIEW";W[W.LATENCY_ACTION_PREFETCH]="LATENCY_ACTION_PREFETCH";W[W.LATENCY_ACTION_ABANDONED_WATCH]="LATENCY_ACTION_ABANDONED_WATCH";W[W.LATENCY_ACTION_LOAD_COMMENT_REPLIES]="LATENCY_ACTION_LOAD_COMMENT_REPLIES";W[W.LATENCY_ACTION_LOAD_COMMENTS]="LATENCY_ACTION_LOAD_COMMENTS";W[W.LATENCY_ACTION_EDIT_COMMENT]="LATENCY_ACTION_EDIT_COMMENT";W[W.LATENCY_ACTION_NEW_COMMENT]="LATENCY_ACTION_NEW_COMMENT";
W[W.LATENCY_ACTION_OFFLINE_SHARING_RECEIVER_PAIRING]="LATENCY_ACTION_OFFLINE_SHARING_RECEIVER_PAIRING";W[W.LATENCY_ACTION_EMBED]="LATENCY_ACTION_EMBED";W[W.LATENCY_ACTION_MDX_LAUNCH]="LATENCY_ACTION_MDX_LAUNCH";W[W.LATENCY_ACTION_RESOLVE_URL]="LATENCY_ACTION_RESOLVE_URL";W[W.LATENCY_ACTION_CAST_SPLASH]="LATENCY_ACTION_CAST_SPLASH";W[W.LATENCY_ACTION_MDX_CAST]="LATENCY_ACTION_MDX_CAST";W[W.LATENCY_ACTION_MDX_COMMAND]="LATENCY_ACTION_MDX_COMMAND";W[W.LATENCY_ACTION_REEL_SELECT_SEGMENT]="LATENCY_ACTION_REEL_SELECT_SEGMENT";
W[W.LATENCY_ACTION_ACCELERATED_EFFECTS]="LATENCY_ACTION_ACCELERATED_EFFECTS";W[W.LATENCY_ACTION_UPLOAD_AUDIO_MIXER]="LATENCY_ACTION_UPLOAD_AUDIO_MIXER";W[W.LATENCY_ACTION_SHORTS_SEG_IMP_TRANSCODING]="LATENCY_ACTION_SHORTS_SEG_IMP_TRANSCODING";W[W.LATENCY_ACTION_SHORTS_AUDIO_PICKER_PLAYBACK]="LATENCY_ACTION_SHORTS_AUDIO_PICKER_PLAYBACK";W[W.LATENCY_ACTION_SHORTS_WAVEFORM_DOWNLOAD]="LATENCY_ACTION_SHORTS_WAVEFORM_DOWNLOAD";W[W.LATENCY_ACTION_SHORTS_VIDEO_INGESTION]="LATENCY_ACTION_SHORTS_VIDEO_INGESTION";
W[W.LATENCY_ACTION_SHORTS_GALLERY]="LATENCY_ACTION_SHORTS_GALLERY";W[W.LATENCY_ACTION_SHORTS_TRIM]="LATENCY_ACTION_SHORTS_TRIM";W[W.LATENCY_ACTION_SHORTS_EDIT]="LATENCY_ACTION_SHORTS_EDIT";W[W.LATENCY_ACTION_SHORTS_CAMERA]="LATENCY_ACTION_SHORTS_CAMERA";W[W.LATENCY_ACTION_PARENT_TOOLS_DASHBOARD]="LATENCY_ACTION_PARENT_TOOLS_DASHBOARD";W[W.LATENCY_ACTION_PARENT_TOOLS_COLLECTION]="LATENCY_ACTION_PARENT_TOOLS_COLLECTION";W[W.LATENCY_ACTION_MUSIC_LOAD_RECOMMENDED_MEDIA_ITEMS]="LATENCY_ACTION_MUSIC_LOAD_RECOMMENDED_MEDIA_ITEMS";
W[W.LATENCY_ACTION_MUSIC_LOAD_MEDIA_ITEMS]="LATENCY_ACTION_MUSIC_LOAD_MEDIA_ITEMS";W[W.LATENCY_ACTION_MUSIC_ALBUM_DETAIL]="LATENCY_ACTION_MUSIC_ALBUM_DETAIL";W[W.LATENCY_ACTION_MUSIC_PLAYLIST_DETAIL]="LATENCY_ACTION_MUSIC_PLAYLIST_DETAIL";W[W.LATENCY_ACTION_CHIPS]="LATENCY_ACTION_CHIPS";W[W.LATENCY_ACTION_SEARCH_ZERO_STATE]="LATENCY_ACTION_SEARCH_ZERO_STATE";W[W.LATENCY_ACTION_LIVE_PAGINATION]="LATENCY_ACTION_LIVE_PAGINATION";W[W.LATENCY_ACTION_LIVE]="LATENCY_ACTION_LIVE";
W[W.LATENCY_ACTION_PREBUFFER]="LATENCY_ACTION_PREBUFFER";W[W.LATENCY_ACTION_TENX]="LATENCY_ACTION_TENX";W[W.LATENCY_ACTION_KIDS_PROFILE_SETTINGS]="LATENCY_ACTION_KIDS_PROFILE_SETTINGS";W[W.LATENCY_ACTION_KIDS_WATCH_IT_AGAIN]="LATENCY_ACTION_KIDS_WATCH_IT_AGAIN";W[W.LATENCY_ACTION_KIDS_SECRET_CODE]="LATENCY_ACTION_KIDS_SECRET_CODE";W[W.LATENCY_ACTION_KIDS_PARENT_PROFILE_SETTINGS]="LATENCY_ACTION_KIDS_PARENT_PROFILE_SETTINGS";W[W.LATENCY_ACTION_KIDS_ONBOARDING]="LATENCY_ACTION_KIDS_ONBOARDING";
W[W.LATENCY_ACTION_KIDS_VOICE_SEARCH]="LATENCY_ACTION_KIDS_VOICE_SEARCH";W[W.LATENCY_ACTION_KIDS_CURATED_COLLECTION]="LATENCY_ACTION_KIDS_CURATED_COLLECTION";W[W.LATENCY_ACTION_KIDS_LIBRARY]="LATENCY_ACTION_KIDS_LIBRARY";W[W.LATENCY_ACTION_CREATOR_VIDEO_TRANSLATIONS]="LATENCY_ACTION_CREATOR_VIDEO_TRANSLATIONS";W[W.LATENCY_ACTION_CREATOR_VIDEO_MONETIZATION]="LATENCY_ACTION_CREATOR_VIDEO_MONETIZATION";W[W.LATENCY_ACTION_CREATOR_VIDEO_LIVE_STREAMING]="LATENCY_ACTION_CREATOR_VIDEO_LIVE_STREAMING";
W[W.LATENCY_ACTION_CREATOR_VIDEO_LIVE_SETTINGS]="LATENCY_ACTION_CREATOR_VIDEO_LIVE_SETTINGS";W[W.LATENCY_ACTION_CREATOR_VIDEO_EDITOR_ASYNC]="LATENCY_ACTION_CREATOR_VIDEO_EDITOR_ASYNC";W[W.LATENCY_ACTION_CREATOR_VIDEO_EDITOR]="LATENCY_ACTION_CREATOR_VIDEO_EDITOR";W[W.LATENCY_ACTION_CREATOR_VIDEO_EDIT]="LATENCY_ACTION_CREATOR_VIDEO_EDIT";W[W.LATENCY_ACTION_CREATOR_VIDEO_COMMENTS]="LATENCY_ACTION_CREATOR_VIDEO_COMMENTS";W[W.LATENCY_ACTION_CREATOR_VIDEO_ANALYTICS]="LATENCY_ACTION_CREATOR_VIDEO_ANALYTICS";
W[W.LATENCY_ACTION_CREATOR_POST_LIST]="LATENCY_ACTION_CREATOR_POST_LIST";W[W.LATENCY_ACTION_CREATOR_POST_EDIT]="LATENCY_ACTION_CREATOR_POST_EDIT";W[W.LATENCY_ACTION_CREATOR_POST_COMMENTS]="LATENCY_ACTION_CREATOR_POST_COMMENTS";W[W.LATENCY_ACTION_CREATOR_LIVE_STREAMING]="LATENCY_ACTION_CREATOR_LIVE_STREAMING";W[W.LATENCY_ACTION_CREATOR_DIALOG_UPLOADS]="LATENCY_ACTION_CREATOR_DIALOG_UPLOADS";W[W.LATENCY_ACTION_CREATOR_DIALOG_COPYRIGHT_STRIKES]="LATENCY_ACTION_CREATOR_DIALOG_COPYRIGHT_STRIKES";
W[W.LATENCY_ACTION_CREATOR_CHANNEL_VIDEOS]="LATENCY_ACTION_CREATOR_CHANNEL_VIDEOS";W[W.LATENCY_ACTION_CREATOR_CHANNEL_TRANSLATIONS]="LATENCY_ACTION_CREATOR_CHANNEL_TRANSLATIONS";W[W.LATENCY_ACTION_CREATOR_CHANNEL_PLAYLISTS]="LATENCY_ACTION_CREATOR_CHANNEL_PLAYLISTS";W[W.LATENCY_ACTION_CREATOR_CHANNEL_MUSIC]="LATENCY_ACTION_CREATOR_CHANNEL_MUSIC";W[W.LATENCY_ACTION_CREATOR_CHANNEL_MONETIZATION]="LATENCY_ACTION_CREATOR_CHANNEL_MONETIZATION";W[W.LATENCY_ACTION_CREATOR_CHANNEL_EDITING]="LATENCY_ACTION_CREATOR_CHANNEL_EDITING";
W[W.LATENCY_ACTION_CREATOR_CHANNEL_DASHBOARD]="LATENCY_ACTION_CREATOR_CHANNEL_DASHBOARD";W[W.LATENCY_ACTION_CREATOR_CHANNEL_COPYRIGHT]="LATENCY_ACTION_CREATOR_CHANNEL_COPYRIGHT";W[W.LATENCY_ACTION_CREATOR_CHANNEL_COMMENTS]="LATENCY_ACTION_CREATOR_CHANNEL_COMMENTS";W[W.LATENCY_ACTION_CREATOR_CHANNEL_ANALYTICS]="LATENCY_ACTION_CREATOR_CHANNEL_ANALYTICS";W[W.LATENCY_ACTION_CREATOR_ARTIST_PROFILE]="LATENCY_ACTION_CREATOR_ARTIST_PROFILE";W[W.LATENCY_ACTION_CREATOR_ARTIST_CONCERTS]="LATENCY_ACTION_CREATOR_ARTIST_CONCERTS";
W[W.LATENCY_ACTION_CREATOR_ARTIST_ANALYTICS]="LATENCY_ACTION_CREATOR_ARTIST_ANALYTICS";W[W.LATENCY_ACTION_CREATOR_ANALYTICS_EXPLORE]="LATENCY_ACTION_CREATOR_ANALYTICS_EXPLORE";W[W.LATENCY_ACTION_STORYBOARD_THUMBNAILS]="LATENCY_ACTION_STORYBOARD_THUMBNAILS";W[W.LATENCY_ACTION_SEARCH_THUMBNAILS]="LATENCY_ACTION_SEARCH_THUMBNAILS";W[W.LATENCY_ACTION_ON_DEVICE_MODEL_DOWNLOAD]="LATENCY_ACTION_ON_DEVICE_MODEL_DOWNLOAD";W[W.LATENCY_ACTION_VOICE_ASSISTANT]="LATENCY_ACTION_VOICE_ASSISTANT";
W[W.LATENCY_ACTION_SEARCH_UI]="LATENCY_ACTION_SEARCH_UI";W[W.LATENCY_ACTION_SUGGEST]="LATENCY_ACTION_SUGGEST";W[W.LATENCY_ACTION_AUTO_SEARCH]="LATENCY_ACTION_AUTO_SEARCH";W[W.LATENCY_ACTION_DOWNLOADS]="LATENCY_ACTION_DOWNLOADS";W[W.LATENCY_ACTION_EXPLORE]="LATENCY_ACTION_EXPLORE";W[W.LATENCY_ACTION_VIDEO_LIST]="LATENCY_ACTION_VIDEO_LIST";W[W.LATENCY_ACTION_HOME_RESUME]="LATENCY_ACTION_HOME_RESUME";W[W.LATENCY_ACTION_SUBSCRIPTIONS_LIST]="LATENCY_ACTION_SUBSCRIPTIONS_LIST";
W[W.LATENCY_ACTION_THUMBNAIL_LOAD]="LATENCY_ACTION_THUMBNAIL_LOAD";W[W.LATENCY_ACTION_FIRST_THUMBNAIL_LOAD]="LATENCY_ACTION_FIRST_THUMBNAIL_LOAD";W[W.LATENCY_ACTION_SUBSCRIPTIONS_FEED]="LATENCY_ACTION_SUBSCRIPTIONS_FEED";W[W.LATENCY_ACTION_SUBSCRIPTIONS]="LATENCY_ACTION_SUBSCRIPTIONS";W[W.LATENCY_ACTION_TRENDING]="LATENCY_ACTION_TRENDING";W[W.LATENCY_ACTION_LIBRARY]="LATENCY_ACTION_LIBRARY";W[W.LATENCY_ACTION_VIDEO_THUMBNAIL]="LATENCY_ACTION_VIDEO_THUMBNAIL";W[W.LATENCY_ACTION_SHOW_MORE]="LATENCY_ACTION_SHOW_MORE";
W[W.LATENCY_ACTION_VIDEO_PREVIEW]="LATENCY_ACTION_VIDEO_PREVIEW";W[W.LATENCY_ACTION_PREBUFFER_VIDEO]="LATENCY_ACTION_PREBUFFER_VIDEO";W[W.LATENCY_ACTION_PREFETCH_VIDEO]="LATENCY_ACTION_PREFETCH_VIDEO";W[W.LATENCY_ACTION_DIRECT_PLAYBACK]="LATENCY_ACTION_DIRECT_PLAYBACK";W[W.LATENCY_ACTION_REEL_WATCH]="LATENCY_ACTION_REEL_WATCH";W[W.LATENCY_ACTION_AD_TO_AD]="LATENCY_ACTION_AD_TO_AD";W[W.LATENCY_ACTION_VIDEO_TO_AD]="LATENCY_ACTION_VIDEO_TO_AD";W[W.LATENCY_ACTION_AD_TO_VIDEO]="LATENCY_ACTION_AD_TO_VIDEO";
W[W.LATENCY_ACTION_ONBOARDING]="LATENCY_ACTION_ONBOARDING";W[W.LATENCY_ACTION_LOGIN]="LATENCY_ACTION_LOGIN";W[W.LATENCY_ACTION_BROWSE]="LATENCY_ACTION_BROWSE";W[W.LATENCY_ACTION_CHANNELS]="LATENCY_ACTION_CHANNELS";W[W.LATENCY_ACTION_WATCH]="LATENCY_ACTION_WATCH";W[W.LATENCY_ACTION_RESULTS]="LATENCY_ACTION_RESULTS";W[W.LATENCY_ACTION_HOME]="LATENCY_ACTION_HOME";W[W.LATENCY_ACTION_STARTUP]="LATENCY_ACTION_STARTUP";W[W.LATENCY_ACTION_UNKNOWN]="LATENCY_ACTION_UNKNOWN";
var Lr={LATENCY_NETWORK_MOBILE:2,LATENCY_NETWORK_WIFI:1,LATENCY_NETWORK_UNKNOWN:0};Lr[Lr.LATENCY_NETWORK_MOBILE]="LATENCY_NETWORK_MOBILE";Lr[Lr.LATENCY_NETWORK_WIFI]="LATENCY_NETWORK_WIFI";Lr[Lr.LATENCY_NETWORK_UNKNOWN]="LATENCY_NETWORK_UNKNOWN";var X={CONN_INVALID:31,CONN_CELLULAR_5G_NSA:12,CONN_CELLULAR_5G_SA:11,CONN_WIFI_METERED:10,CONN_CELLULAR_5G:9,CONN_DISCO:8,CONN_CELLULAR_UNKNOWN:7,CONN_CELLULAR_4G:6,CONN_CELLULAR_3G:5,CONN_CELLULAR_2G:4,CONN_WIFI:3,CONN_NONE:2,CONN_UNKNOWN:1,CONN_DEFAULT:0};
X[X.CONN_INVALID]="CONN_INVALID";X[X.CONN_CELLULAR_5G_NSA]="CONN_CELLULAR_5G_NSA";X[X.CONN_CELLULAR_5G_SA]="CONN_CELLULAR_5G_SA";X[X.CONN_WIFI_METERED]="CONN_WIFI_METERED";X[X.CONN_CELLULAR_5G]="CONN_CELLULAR_5G";X[X.CONN_DISCO]="CONN_DISCO";X[X.CONN_CELLULAR_UNKNOWN]="CONN_CELLULAR_UNKNOWN";X[X.CONN_CELLULAR_4G]="CONN_CELLULAR_4G";X[X.CONN_CELLULAR_3G]="CONN_CELLULAR_3G";X[X.CONN_CELLULAR_2G]="CONN_CELLULAR_2G";X[X.CONN_WIFI]="CONN_WIFI";X[X.CONN_NONE]="CONN_NONE";X[X.CONN_UNKNOWN]="CONN_UNKNOWN";
X[X.CONN_DEFAULT]="CONN_DEFAULT";
var Y={DETAILED_NETWORK_TYPE_NR_NSA:126,DETAILED_NETWORK_TYPE_NR_SA:125,DETAILED_NETWORK_TYPE_INTERNAL_WIFI_IMPAIRED:124,DETAILED_NETWORK_TYPE_APP_WIFI_HOTSPOT:123,DETAILED_NETWORK_TYPE_DISCONNECTED:122,DETAILED_NETWORK_TYPE_NON_MOBILE_UNKNOWN:121,DETAILED_NETWORK_TYPE_MOBILE_UNKNOWN:120,DETAILED_NETWORK_TYPE_WIMAX:119,DETAILED_NETWORK_TYPE_ETHERNET:118,DETAILED_NETWORK_TYPE_BLUETOOTH:117,DETAILED_NETWORK_TYPE_WIFI:116,DETAILED_NETWORK_TYPE_LTE:115,DETAILED_NETWORK_TYPE_HSPAP:114,DETAILED_NETWORK_TYPE_EHRPD:113,
DETAILED_NETWORK_TYPE_EVDO_B:112,DETAILED_NETWORK_TYPE_UMTS:111,DETAILED_NETWORK_TYPE_IDEN:110,DETAILED_NETWORK_TYPE_HSUPA:109,DETAILED_NETWORK_TYPE_HSPA:108,DETAILED_NETWORK_TYPE_HSDPA:107,DETAILED_NETWORK_TYPE_EVDO_A:106,DETAILED_NETWORK_TYPE_EVDO_0:105,DETAILED_NETWORK_TYPE_CDMA:104,DETAILED_NETWORK_TYPE_1_X_RTT:103,DETAILED_NETWORK_TYPE_GPRS:102,DETAILED_NETWORK_TYPE_EDGE:101,DETAILED_NETWORK_TYPE_UNKNOWN:0};Y[Y.DETAILED_NETWORK_TYPE_NR_NSA]="DETAILED_NETWORK_TYPE_NR_NSA";
Y[Y.DETAILED_NETWORK_TYPE_NR_SA]="DETAILED_NETWORK_TYPE_NR_SA";Y[Y.DETAILED_NETWORK_TYPE_INTERNAL_WIFI_IMPAIRED]="DETAILED_NETWORK_TYPE_INTERNAL_WIFI_IMPAIRED";Y[Y.DETAILED_NETWORK_TYPE_APP_WIFI_HOTSPOT]="DETAILED_NETWORK_TYPE_APP_WIFI_HOTSPOT";Y[Y.DETAILED_NETWORK_TYPE_DISCONNECTED]="DETAILED_NETWORK_TYPE_DISCONNECTED";Y[Y.DETAILED_NETWORK_TYPE_NON_MOBILE_UNKNOWN]="DETAILED_NETWORK_TYPE_NON_MOBILE_UNKNOWN";Y[Y.DETAILED_NETWORK_TYPE_MOBILE_UNKNOWN]="DETAILED_NETWORK_TYPE_MOBILE_UNKNOWN";
Y[Y.DETAILED_NETWORK_TYPE_WIMAX]="DETAILED_NETWORK_TYPE_WIMAX";Y[Y.DETAILED_NETWORK_TYPE_ETHERNET]="DETAILED_NETWORK_TYPE_ETHERNET";Y[Y.DETAILED_NETWORK_TYPE_BLUETOOTH]="DETAILED_NETWORK_TYPE_BLUETOOTH";Y[Y.DETAILED_NETWORK_TYPE_WIFI]="DETAILED_NETWORK_TYPE_WIFI";Y[Y.DETAILED_NETWORK_TYPE_LTE]="DETAILED_NETWORK_TYPE_LTE";Y[Y.DETAILED_NETWORK_TYPE_HSPAP]="DETAILED_NETWORK_TYPE_HSPAP";Y[Y.DETAILED_NETWORK_TYPE_EHRPD]="DETAILED_NETWORK_TYPE_EHRPD";Y[Y.DETAILED_NETWORK_TYPE_EVDO_B]="DETAILED_NETWORK_TYPE_EVDO_B";
Y[Y.DETAILED_NETWORK_TYPE_UMTS]="DETAILED_NETWORK_TYPE_UMTS";Y[Y.DETAILED_NETWORK_TYPE_IDEN]="DETAILED_NETWORK_TYPE_IDEN";Y[Y.DETAILED_NETWORK_TYPE_HSUPA]="DETAILED_NETWORK_TYPE_HSUPA";Y[Y.DETAILED_NETWORK_TYPE_HSPA]="DETAILED_NETWORK_TYPE_HSPA";Y[Y.DETAILED_NETWORK_TYPE_HSDPA]="DETAILED_NETWORK_TYPE_HSDPA";Y[Y.DETAILED_NETWORK_TYPE_EVDO_A]="DETAILED_NETWORK_TYPE_EVDO_A";Y[Y.DETAILED_NETWORK_TYPE_EVDO_0]="DETAILED_NETWORK_TYPE_EVDO_0";Y[Y.DETAILED_NETWORK_TYPE_CDMA]="DETAILED_NETWORK_TYPE_CDMA";
Y[Y.DETAILED_NETWORK_TYPE_1_X_RTT]="DETAILED_NETWORK_TYPE_1_X_RTT";Y[Y.DETAILED_NETWORK_TYPE_GPRS]="DETAILED_NETWORK_TYPE_GPRS";Y[Y.DETAILED_NETWORK_TYPE_EDGE]="DETAILED_NETWORK_TYPE_EDGE";Y[Y.DETAILED_NETWORK_TYPE_UNKNOWN]="DETAILED_NETWORK_TYPE_UNKNOWN";var Mr={LATENCY_PLAYER_RTSP:7,LATENCY_PLAYER_HTML5_INLINE:6,LATENCY_PLAYER_HTML5_FULLSCREEN:5,LATENCY_PLAYER_HTML5:4,LATENCY_PLAYER_FRAMEWORK:3,LATENCY_PLAYER_FLASH:2,LATENCY_PLAYER_EXO:1,LATENCY_PLAYER_UNKNOWN:0};Mr[Mr.LATENCY_PLAYER_RTSP]="LATENCY_PLAYER_RTSP";
Mr[Mr.LATENCY_PLAYER_HTML5_INLINE]="LATENCY_PLAYER_HTML5_INLINE";Mr[Mr.LATENCY_PLAYER_HTML5_FULLSCREEN]="LATENCY_PLAYER_HTML5_FULLSCREEN";Mr[Mr.LATENCY_PLAYER_HTML5]="LATENCY_PLAYER_HTML5";Mr[Mr.LATENCY_PLAYER_FRAMEWORK]="LATENCY_PLAYER_FRAMEWORK";Mr[Mr.LATENCY_PLAYER_FLASH]="LATENCY_PLAYER_FLASH";Mr[Mr.LATENCY_PLAYER_EXO]="LATENCY_PLAYER_EXO";Mr[Mr.LATENCY_PLAYER_UNKNOWN]="LATENCY_PLAYER_UNKNOWN";
var Nr={LATENCY_AD_BREAK_TYPE_POSTROLL:3,LATENCY_AD_BREAK_TYPE_MIDROLL:2,LATENCY_AD_BREAK_TYPE_PREROLL:1,LATENCY_AD_BREAK_TYPE_UNKNOWN:0};Nr[Nr.LATENCY_AD_BREAK_TYPE_POSTROLL]="LATENCY_AD_BREAK_TYPE_POSTROLL";Nr[Nr.LATENCY_AD_BREAK_TYPE_MIDROLL]="LATENCY_AD_BREAK_TYPE_MIDROLL";Nr[Nr.LATENCY_AD_BREAK_TYPE_PREROLL]="LATENCY_AD_BREAK_TYPE_PREROLL";Nr[Nr.LATENCY_AD_BREAK_TYPE_UNKNOWN]="LATENCY_AD_BREAK_TYPE_UNKNOWN";var Or={LATENCY_ACTION_ERROR_STARTUP_TIMEOUT:1,LATENCY_ACTION_ERROR_UNSPECIFIED:0};
Or[Or.LATENCY_ACTION_ERROR_STARTUP_TIMEOUT]="LATENCY_ACTION_ERROR_STARTUP_TIMEOUT";Or[Or.LATENCY_ACTION_ERROR_UNSPECIFIED]="LATENCY_ACTION_ERROR_UNSPECIFIED";var Pr={LIVE_STREAM_MODE_WINDOW:5,LIVE_STREAM_MODE_POST:4,LIVE_STREAM_MODE_LP:3,LIVE_STREAM_MODE_LIVE:2,LIVE_STREAM_MODE_DVR:1,LIVE_STREAM_MODE_UNKNOWN:0};Pr[Pr.LIVE_STREAM_MODE_WINDOW]="LIVE_STREAM_MODE_WINDOW";Pr[Pr.LIVE_STREAM_MODE_POST]="LIVE_STREAM_MODE_POST";Pr[Pr.LIVE_STREAM_MODE_LP]="LIVE_STREAM_MODE_LP";
Pr[Pr.LIVE_STREAM_MODE_LIVE]="LIVE_STREAM_MODE_LIVE";Pr[Pr.LIVE_STREAM_MODE_DVR]="LIVE_STREAM_MODE_DVR";Pr[Pr.LIVE_STREAM_MODE_UNKNOWN]="LIVE_STREAM_MODE_UNKNOWN";var Qr={VIDEO_STREAM_TYPE_VOD:3,VIDEO_STREAM_TYPE_DVR:2,VIDEO_STREAM_TYPE_LIVE:1,VIDEO_STREAM_TYPE_UNSPECIFIED:0};Qr[Qr.VIDEO_STREAM_TYPE_VOD]="VIDEO_STREAM_TYPE_VOD";Qr[Qr.VIDEO_STREAM_TYPE_DVR]="VIDEO_STREAM_TYPE_DVR";Qr[Qr.VIDEO_STREAM_TYPE_LIVE]="VIDEO_STREAM_TYPE_LIVE";Qr[Qr.VIDEO_STREAM_TYPE_UNSPECIFIED]="VIDEO_STREAM_TYPE_UNSPECIFIED";
var Rr={YT_IDB_TRANSACTION_TYPE_READ:2,YT_IDB_TRANSACTION_TYPE_WRITE:1,YT_IDB_TRANSACTION_TYPE_UNKNOWN:0};Rr[Rr.YT_IDB_TRANSACTION_TYPE_READ]="YT_IDB_TRANSACTION_TYPE_READ";Rr[Rr.YT_IDB_TRANSACTION_TYPE_WRITE]="YT_IDB_TRANSACTION_TYPE_WRITE";Rr[Rr.YT_IDB_TRANSACTION_TYPE_UNKNOWN]="YT_IDB_TRANSACTION_TYPE_UNKNOWN";var Sr={PLAYER_ROTATION_TYPE_PORTRAIT_TO_FULLSCREEN:2,PLAYER_ROTATION_TYPE_FULLSCREEN_TO_PORTRAIT:1,PLAYER_ROTATION_TYPE_UNKNOWN:0};Sr[Sr.PLAYER_ROTATION_TYPE_PORTRAIT_TO_FULLSCREEN]="PLAYER_ROTATION_TYPE_PORTRAIT_TO_FULLSCREEN";
Sr[Sr.PLAYER_ROTATION_TYPE_FULLSCREEN_TO_PORTRAIT]="PLAYER_ROTATION_TYPE_FULLSCREEN_TO_PORTRAIT";Sr[Sr.PLAYER_ROTATION_TYPE_UNKNOWN]="PLAYER_ROTATION_TYPE_UNKNOWN";var Tr="actionVisualElement spinnerInfo resourceInfo playerInfo commentInfo mdxInfo watchInfo thumbnailLoadInfo creatorInfo unpluggedInfo reelInfo subscriptionsFeedInfo requestIds mediaBrowserActionInfo musicLoadActionInfo shoppingInfo prefetchInfo accelerationSession webInfo tvInfo kabukiInfo mwebInfo musicInfo".split(" ");var Ur=x.ytLoggingLatencyUsageStats_||{};y("ytLoggingLatencyUsageStats_",Ur);function Vr(){this.h=0}
function Wr(){Vr.h||(Vr.h=new Vr);return Vr.h}
Vr.prototype.tick=function(a,b,c,d){Xr(this,"tick_"+a+"_"+b)||(c={timestamp:c,cttAuthInfo:d},M("web_csi_via_jspb")?(d=new xh,D(d,1,a),D(d,2,b),a=new Ah,nd(a,5,Bh,d),zp(a,c)):kk("latencyActionTicked",{tickName:a,clientActionNonce:b},c))};
Vr.prototype.info=function(a,b,c){var d=Object.keys(a).join("");Xr(this,"info_"+d+"_"+b)||(a=Object.assign({},a),a.clientActionNonce=b,kk("latencyActionInfo",a,{cttAuthInfo:c}))};
Vr.prototype.jspbInfo=function(a,b,c){for(var d="",e=0;e<a.toJSON().length;e++)void 0!==a.toJSON()[e]&&(d=0===e?d.concat(""+e):d.concat("_"+e));Xr(this,"info_"+d+"_"+b)||(D(a,2,b),b={cttAuthInfo:c},c=new Ah,nd(c,7,Bh,a),zp(c,b))};
Vr.prototype.span=function(a,b,c){var d=Object.keys(a).join("");Xr(this,"span_"+d+"_"+b)||(a.clientActionNonce=b,kk("latencyActionSpan",a,{cttAuthInfo:c}))};
function Xr(a,b){Ur[b]=Ur[b]||{count:0};var c=Ur[b];c.count++;c.time=P();a.h||(a.h=Uj(function(){var d=P(),e;for(e in Ur)Ur[e]&&6E4<d-Ur[e].time&&delete Ur[e];a&&(a.h=0)},5E3));
return 5<c.count?(6===c.count&&1>1E5*Math.random()&&(c=new Q("CSI data exceeded logging limit with key",b.split("_")),0<=b.indexOf("plev")||Np(c)),!0):!1}
;function Yr(){var a=["ol"];Cr("").info.actionType="embed";a&&Xh("TIMING_AFT_KEYS",a);Xh("TIMING_ACTION","embed");Zr();a=ur();var b=wr();if("cold"===a.yt_lt||"cold"===b.loadType){var c=pr(),d=vr();d=d.gelTicks?d.gelTicks:d.gelTicks={};for(var e in c)e in d||Z(e,c[e]);e={};c=!1;d=p(Object.keys(a));for(var f=d.next();!f.done;f=d.next())f=f.value,(f=Kr(f,a[f]))&&!zr(wr(),f)&&(dr(b,f),dr(e,f),c=!0);c&&$r(e)}y("ytglobal.timingready_",!0);a=A("TIMING_ACTION");z("ytglobal.timingready_")&&a&&"_start"in pr()&&
or()&&yr()}
function as(a,b,c,d){null!==b&&(ur(c)[a]=b,(a=Kr(a,b,c))&&$r(a,c,d))}
function $r(a,b,c){if(!M("web_csi_via_jspb")||(void 0===c?0:c))c=Cr(b||""),dr(c.info,a),dr(wr(b),a),c=xr(b),b=tr(b).cttAuthInfo,Wr().info(a,c,b);else{c=new th;var d=Object.keys(a);a=Object.values(a);for(var e=0;e<d.length;e++){var f=d[e];try{switch(f){case "actionType":D(c,1,W[a[e]]);break;case "clientActionNonce":D(c,2,a[e]);break;case "clientScreenNonce":D(c,4,a[e]);break;case "loadType":D(c,3,a[e]);break;case "isPrewarmedLaunch":D(c,92,a[e]);break;case "isFirstInstall":D(c,55,a[e]);break;case "networkType":D(c,
5,Lr[a[e]]);break;case "connectionType":D(c,26,X[a[e]]);break;case "detailedConnectionType":D(c,27,Y[a[e]]);break;case "isVisible":D(c,6,a[e]);break;case "playerType":D(c,7,Mr[a[e]]);break;case "clientPlaybackNonce":D(c,8,a[e]);break;case "adClientPlaybackNonce":D(c,28,a[e]);break;case "previousCpn":D(c,77,a[e]);break;case "targetCpn":D(c,76,a[e]);break;case "isMonetized":D(c,9,a[e]);break;case "isPrerollAllowed":D(c,16,a[e]);break;case "isPrerollShown":D(c,17,a[e]);break;case "adType":D(c,12,a[e]);
break;case "adTypesAllowed":D(c,36,a[e]);break;case "adNetworks":D(c,37,a[e]);break;case "previousAction":D(c,13,W[a[e]]);break;case "isRedSubscriber":D(c,14,a[e]);break;case "serverTimeMs":D(c,15,a[e]);break;case "videoId":c.setVideoId(a[e]);break;case "adVideoId":D(c,20,a[e]);break;case "targetVideoId":D(c,78,a[e]);break;case "adBreakType":D(c,21,Nr[a[e]]);break;case "isNavigation":D(c,25,a[e]);break;case "viewportHeight":D(c,29,a[e]);break;case "viewportWidth":D(c,30,a[e]);break;case "screenHeight":D(c,
84,a[e]);break;case "screenWidth":D(c,85,a[e]);break;case "browseId":D(c,31,a[e]);break;case "isCacheHit":D(c,32,a[e]);break;case "httpProtocol":D(c,33,a[e]);break;case "transportProtocol":D(c,34,a[e]);break;case "searchQuery":D(c,41,a[e]);break;case "isContinuation":D(c,42,a[e]);break;case "availableProcessors":D(c,43,a[e]);break;case "sdk":D(c,44,a[e]);break;case "isLocalStream":D(c,45,a[e]);break;case "navigationRequestedSameUrl":D(c,64,a[e]);break;case "shellStartupDurationMs":D(c,70,a[e]);break;
case "appInstallDataAgeMs":D(c,73,a[e]);break;case "latencyActionError":D(c,71,Or[a[e]]);break;case "actionStep":D(c,79,a[e]);break;case "jsHeapSizeLimit":D(c,80,a[e]);break;case "totalJsHeapSize":D(c,81,a[e]);break;case "usedJsHeapSize":D(c,82,a[e]);break;case "sourceVideoDurationMs":D(c,90,a[e]);break;case "adPrebufferedTimeSecs":D(c,39,a[e]);break;case "isLivestream":D(c,47,a[e]);break;case "liveStreamMode":D(c,91,Pr[a[e]]);break;case "adCpn2":D(c,48,a[e]);break;case "adDaiDriftMillis":D(c,49,
a[e]);break;case "videoStreamType":D(c,53,Qr[a[e]]);break;case "playbackRequiresTap":D(c,56,a[e]);break;case "performanceNavigationTiming":D(c,67,a[e]);break;case "transactionType":D(c,74,Rr[a[e]]);break;case "playerRotationType":D(c,101,Sr[a[e]]);break;case "allowedPreroll":D(c,10,a[e]);break;case "shownPreroll":D(c,11,a[e]);break;case "getHomeRequestId":D(c,57,a[e]);break;case "getSearchRequestId":D(c,60,a[e]);break;case "getPlayerRequestId":D(c,61,a[e]);break;case "getWatchNextRequestId":D(c,62,
a[e]);break;case "getBrowseRequestId":D(c,63,a[e]);break;case "getLibraryRequestId":D(c,66,a[e]);break;default:Tr.includes(f)&&fi(new Q("Codegen laipb translator asked to translate message field",""+f))}}catch(g){fi(Error("Codegen laipb translator failed to set "+f))}}bs(c,b)}}
function bs(a,b){var c=vr(b);c.jspbInfos||(c.jspbInfos=[]);c.jspbInfos.push(a);Cr(b||"").jspbInfo.push(a);c=xr(b);b=tr(b).cttAuthInfo;Wr().jspbInfo(a,c,b)}
function Z(a,b,c){if(!b&&"_"!==a[0]){var d=a;T.mark&&(0==d.lastIndexOf("mark_",0)||(d="mark_"+d),c&&(d+=" ("+c+")"),T.mark(d))}Cr(c||"").tick[a]=b||P();d=vr(c);d.gelTicks&&(d.gelTicks[a]=!0);d=pr(c);var e=b||P();d[a]=e;e=xr(c);var f=tr(c).cttAuthInfo;if("_start"===a){var g=Wr();Xr(g,"baseline_"+e)||(b={timestamp:b,cttAuthInfo:f},M("web_csi_via_jspb")?(f=new rh,D(f,1,e),e=new Ah,nd(e,6,Bh,f),zp(e,b)):kk("latencyActionBaselined",{clientActionNonce:e},b))}else Wr().tick(a,e,b,f);yr(c);return d[a]}
function cs(){var a=xr();requestAnimationFrame(function(){setTimeout(function(){a===xr()&&Z("ol",void 0,void 0)},0)})}
function ds(){var a=document;if("visibilityState"in a)a=a.visibilityState;else{var b=sn+"VisibilityState";a=b in a?a[b]:void 0}switch(a){case "hidden":return 0;case "visible":return 1;case "prerender":return 2;case "unloaded":return 3;default:return-1}}
function Zr(){function a(f){var g=qr(),h=sr();h&&(Z("srt",g.responseStart),1!==f.prerender&&Z("_start",h,void 0));f=Ar();0<f&&Z("fpt",f);f=qr();f.isPerformanceNavigationTiming&&$r({performanceNavigationTiming:!0});Z("nreqs",f.requestStart,void 0);Z("nress",f.responseStart,void 0);Z("nrese",f.responseEnd,void 0);0<f.redirectEnd-f.redirectStart&&(Z("nrs",f.redirectStart,void 0),Z("nre",f.redirectEnd,void 0));0<f.domainLookupEnd-f.domainLookupStart&&(Z("ndnss",f.domainLookupStart,void 0),Z("ndnse",f.domainLookupEnd,
void 0));0<f.connectEnd-f.connectStart&&(Z("ntcps",f.connectStart,void 0),Z("ntcpe",f.connectEnd,void 0));f.secureConnectionStart>=sr()&&0<f.connectEnd-f.secureConnectionStart&&(Z("nstcps",f.secureConnectionStart,void 0),Z("ntcpe",f.connectEnd,void 0));T&&"getEntriesByType"in T&&es()}
var b=A("TIMING_INFO",{});if(M("web_csi_via_jspb")){b=fs(b);bs(b);b=new th;D(b,25,!0);D(b,1,W[Jr(A("TIMING_ACTION"))]);var c=A("PREVIOUS_ACTION");c&&D(b,13,W[Jr(c)]);(c=A("CLIENT_PROTOCOL"))&&D(b,33,c);(c=A("CLIENT_TRANSPORT"))&&D(b,34,c);(c=eq())&&"UNDEFINED_CSN"!==c&&D(b,4,c);c=ds();1!==c&&-1!==c||D(b,6,!0);c=ur();D(b,3,"cold");a(c);c=gs();if(0<c.length){c=p(c);for(var d=c.next();!d.done;d=c.next()){d=d.value;var e=new sh;D(e,1,d);od(b,83,sh,e)}}bs(b)}else{for(c in b)b.hasOwnProperty(c)&&as(c,b[c]);
b={isNavigation:!0,actionType:Jr(A("TIMING_ACTION"))};if(c=A("PREVIOUS_ACTION"))b.previousAction=Jr(c);if(c=A("CLIENT_PROTOCOL"))b.httpProtocol=c;if(c=A("CLIENT_TRANSPORT"))b.transportProtocol=c;(c=eq())&&"UNDEFINED_CSN"!==c&&(b.clientScreenNonce=c);c=ds();if(1===c||-1===c)b.isVisible=!0;c=ur();b.loadType="cold";a(c);c=gs();if(0<c.length)for(b.resourceInfo=[],c=p(c),d=c.next();!d.done;d=c.next())b.resourceInfo.push({resourceCache:d.value});$r(b)}}
function fs(a){var b=new th;a=p(Object.entries(a));for(var c=a.next();!c.done;c=a.next()){var d=p(c.value);c=d.next().value;d=d.next().value;switch(c){case "GetBrowse_rid":var e=new wh;D(e,1,c);D(e,2,String(d));vh(b,e);break;case "GetGuide_rid":e=new wh;D(e,1,c);D(e,2,String(d));vh(b,e);break;case "GetHome_rid":e=new wh;D(e,1,c);D(e,2,String(d));vh(b,e);break;case "GetPlayer_rid":e=new wh;D(e,1,c);D(e,2,String(d));vh(b,e);break;case "GetSearch_rid":e=new wh;D(e,1,c);D(e,2,String(d));vh(b,e);break;
case "GetSettings_rid":e=new wh;D(e,1,c);D(e,2,String(d));vh(b,e);break;case "GetTrending_rid":e=new wh;D(e,1,c);D(e,2,String(d));vh(b,e);break;case "GetWatchNext_rid":e=new wh;D(e,1,c);D(e,2,String(d));vh(b,e);break;case "yt_red":D(b,14,!!d);break;case "yt_ad":D(b,9,!!d)}}return b}
function hs(a,b){a=document.querySelector(a);if(!a)return!1;var c="",d=a.nodeName;"SCRIPT"===d?(c=a.src,c||(c=a.getAttribute("data-timing-href"))&&(c=window.location.protocol+c)):"LINK"===d&&(c=a.href);Yb()&&a.setAttribute("nonce",Yb());return c?(a=T.getEntriesByName(c))&&a[0]&&(a=a[0],c=sr(),Z("rsf_"+b,c+Math.round(a.fetchStart)),Z("rse_"+b,c+Math.round(a.responseEnd)),void 0!==a.transferSize&&0===a.transferSize)?!0:!1:!1}
function gs(){var a=[];if(document.querySelector&&T&&T.getEntriesByName)for(var b in nr)if(nr.hasOwnProperty(b)){var c=nr[b];hs(b,c)&&a.push(c)}return a}
function es(){var a=window.location.protocol,b=T.getEntriesByType("resource");b=gb(b,function(c){return 0===c.name.indexOf(a+"//fonts.gstatic.com/s/")});
(b=ib(b,function(c,d){return d.duration>c.duration?d:c},{duration:0}))&&0<b.startTime&&0<b.responseEnd&&(Z("wffs",rr(b.startTime)),Z("wffe",rr(b.responseEnd)))}
var is=window;is.ytcsi&&(is.ytcsi.info=as,is.ytcsi.tick=Z);var js=["consistency","mss","client_location","entities","store"];function ks(a,b,c,d){this.o=a;this.J=b;this.l=c;this.j=d;this.i=void 0;this.h=new Map;a.za||(a.za={});a.za=Object.assign({},cr,a.za)}
function ls(a,b,c,d){if(void 0!==ks.h){if(d=ks.h,a=[a!==d.o,b!==d.J,c!==d.l,!1,!1,void 0!==d.i],a.some(function(e){return e}))throw new Q("InnerTubeTransportService is already initialized",a);
}else ks.h=new ks(a,b,c,d)}
function ms(a){var b={signalServiceEndpoint:{signal:"GET_DATASYNC_IDS"}};var c=void 0===c?Lq:c;var d=Uq(b,a.o);if(!d)return bg(new Q("Error: No request builder found for command.",b));var e=d.o(b,void 0,c);return e?new Xf(function(f){var g,h,k;return w(function(m){if(1==m.h){h="cors"===(null==(g=e.ra)?void 0:g.mode)?"cors":void 0;if(a.l.yc){var q=e.config,u;q=null==q?void 0:null==(u=q.Ga)?void 0:u.sessionIndex;u=Cq({sessionIndex:q});k=Object.assign({},ns(h),u);return m.s(2)}return t(m,os(e.config,
h),3)}2!=m.h&&(k=m.i);f(ps(a,e,k));m.h=0})}):bg(new Q("Error: Failed to build request for command.",b))}
function ps(a,b,c){var d,e,f,g,h,k,m,q,u,C,v,E,F,I,R,O,S,ka;return w(function(N){switch(N.h){case 1:N.s(2);break;case 3:if((d=N.i)&&!d.isExpired())return N.return(Promise.resolve(d.h()));case 2:if((f=null==(e=b.config)?void 0:e.Wo)&&a.h.has(f)&&M("web_memoize_inflight_requests"))return N.return(a.h.get(f));if(null==(g=b)?0:null==(h=g.ba)?0:h.context)for(k=p([]),m=k.next();!m.done;m=k.next())q=m.value,q.Uo(b.ba.context);if(null==(u=a.i)?0:u.l(b.input,b.ba))return N.return(a.i.j(b.input,b.ba));C=JSON.stringify(b.ba);
b.ra=Object.assign({},b.ra,{headers:c});v=Object.assign({},b.ra);"POST"===b.ra.method&&(v=Object.assign({},v,{body:C}));(null==(E=b.config)?0:E.jc)&&Z(b.config.jc);F=a.J.fetch(b.input,v,b.config);f&&a.h.set(f,F);return t(N,F,4);case 4:I=N.i;f&&a.h.has(f)&&a.h.delete(f);(null==(R=b.config)?0:R.kc)&&Z(b.config.kc);if(I||null==(O=a.i)||!O.h(b.input,b.ba)){N.s(5);break}return t(N,a.i.i(b.input,b.ba),6);case 6:I=N.i;case 5:if(I&&a.j)for(S=p(js),m=S.next();!m.done;m=S.next())ka=m.value,a.j[ka]&&a.j[ka].handleResponse(I,
b);return N.return(I)}})}
function os(a,b){var c,d,e,f;return w(function(g){if(1==g.h){e=null==(c=a)?void 0:null==(d=c.Ga)?void 0:d.sessionIndex;var h=Cq({sessionIndex:e});if(!(h instanceof Xf)){var k=new Xf(cb);Yf(k,2,h);h=k}return t(g,h,2)}f=g.i;return g.return(Promise.resolve(Object.assign({},ns(b),f)))})}
function ns(a){var b={"Content-Type":"application/json"};M("enable_web_eom_visitor_data")&&A("EOM_VISITOR_DATA")?b["X-Goog-EOM-Visitor-Id"]=A("EOM_VISITOR_DATA"):A("VISITOR_DATA")&&(b["X-Goog-Visitor-Id"]=A("VISITOR_DATA"));"cors"!==a&&((a=A("INNERTUBE_CONTEXT_CLIENT_NAME"))&&(b["X-Youtube-Client-Name"]=a),(a=A("INNERTUBE_CONTEXT_CLIENT_VERSION"))&&(b["X-Youtube-Client-Version"]=a),(a=A("CHROME_CONNECTED_HEADER"))&&(b["X-Youtube-Chrome-Connected"]=a),M("forward_domain_admin_state_on_embeds")&&(a=
A("DOMAIN_ADMIN_STATE"))&&(b["X-Youtube-Domain-Admin-State"]=a));return b}
;var qs=["share/get_web_player_share_panel"],rs=["feedback"],ss=["notification/modify_channel_preference"],ts=["browse/edit_playlist"],us=["subscription/subscribe"],vs=["subscription/unsubscribe"];function ws(){}
r(ws,$q);ws.prototype.j=function(){return us};
ws.prototype.h=function(a){return a.subscribeEndpoint};
ws.prototype.i=function(a,b,c){c=void 0===c?{}:c;b.channelIds&&(a.channelIds=b.channelIds);b.siloName&&(a.siloName=b.siloName);b.params&&(a.params=b.params);c.botguardResponse&&(a.botguardResponse=c.botguardResponse);c.feature&&(a.clientFeature=c.feature)};
da.Object.defineProperties(ws.prototype,{l:{configurable:!0,enumerable:!0,get:function(){return!0}}});function xs(){}
r(xs,$q);xs.prototype.j=function(){return vs};
xs.prototype.h=function(a){return a.unsubscribeEndpoint};
xs.prototype.i=function(a,b){b.channelIds&&(a.channelIds=b.channelIds);b.siloName&&(a.siloName=b.siloName);b.params&&(a.params=b.params)};
da.Object.defineProperties(xs.prototype,{l:{configurable:!0,enumerable:!0,get:function(){return!0}}});function ys(){}
r(ys,$q);ys.prototype.j=function(){return rs};
ys.prototype.h=function(a){return a.feedbackEndpoint};
ys.prototype.i=function(a,b,c){a.feedbackTokens=[];b.feedbackToken&&a.feedbackTokens.push(b.feedbackToken);if(b=b.cpn||c.cpn)a.feedbackContext={cpn:b};a.isFeedbackTokenUnencrypted=!!c.is_feedback_token_unencrypted;a.shouldMerge=!1;c.extra_feedback_tokens&&(a.shouldMerge=!0,a.feedbackTokens=a.feedbackTokens.concat(c.extra_feedback_tokens))};
da.Object.defineProperties(ys.prototype,{l:{configurable:!0,enumerable:!0,get:function(){return!0}}});function zs(){}
r(zs,$q);zs.prototype.j=function(){return ss};
zs.prototype.h=function(a){return a.modifyChannelNotificationPreferenceEndpoint};
zs.prototype.i=function(a,b){b.params&&(a.params=b.params);b.secondaryParams&&(a.secondaryParams=b.secondaryParams)};function As(){}
r(As,$q);As.prototype.j=function(){return ts};
As.prototype.h=function(a){return a.playlistEditEndpoint};
As.prototype.i=function(a,b){b.actions&&(a.actions=b.actions);b.params&&(a.params=b.params);b.playlistId&&(a.playlistId=b.playlistId)};function Bs(){}
r(Bs,$q);Bs.prototype.j=function(){return qs};
Bs.prototype.h=function(a){return a.webPlayerShareEntityServiceEndpoint};
Bs.prototype.i=function(a,b,c){c=void 0===c?{}:c;b.serializedShareEntity&&(a.serializedSharedEntity=b.serializedShareEntity);c.includeListId&&(a.includeListId=!0)};var Gq=new Eq("NETWORK_SLI_TOKEN");function Cs(a){this.h=a}
Cs.prototype.fetch=function(a,b){var c=this,d,e;return w(function(f){c.h&&(d=bc(cc(5,oc(a)))||"/UNKNOWN_PATH",c.h.start(d));e=new window.Request(a,b);return M("web_fetch_promise_cleanup_killswitch")?f.return(Promise.resolve(fetch(e).then(function(g){return c.handleResponse(g)}).catch(function(g){Np(g)}))):f.return(fetch(e).then(function(g){return c.handleResponse(g)}).catch(function(g){Np(g)}))})};
Cs.prototype.handleResponse=function(a){var b=a.text().then(function(c){return JSON.parse(c.replace(")]}'",""))});
a.redirected||a.ok?this.h&&this.h.success():(this.h&&this.h.failure(),b=b.then(function(c){Np(new Q("Error: API fetch failed",a.status,a.url,c));return Object.assign({},c,{errorMetadata:{status:a.status}})}));
return b};
Cs[Dq]=[new Fq];var Ds=new Eq("NETWORK_MANAGER_TOKEN");var Es;function Fs(a){Ql.call(this,1,arguments);this.csn=a}
r(Fs,Ql);var Zl=new Rl("screen-created",Fs),Gs=[],Is=Hs,Js=0;function Ks(a,b,c,d,e,f,g){function h(){Np(new Q("newScreen() parent element does not have a VE - rootVe",b))}
var k=Is();f=new Yp({veType:b,youtubeData:f,jspbYoutubeData:void 0});e={cttAuthInfo:e,X:k};if(M("il_via_jspb")){var m=new hh;m.S(k);ih(m,f.getAsJspb());c&&c.visualElement?(f=new jh,c.clientScreenNonce&&D(f,2,c.clientScreenNonce),kh(f,c.visualElement.getAsJspb()),g&&D(f,4,Ch[g]),H(m,5,f)):c&&h();d&&D(m,3,d);Dp(m,e,a)}else f={csn:k,pageVe:f.getAsJson()},c&&c.visualElement?(f.implicitGesture={parentCsn:c.clientScreenNonce,gesturedVe:c.visualElement.getAsJson()},g&&(f.implicitGesture.gestureType=g)):
c&&h(),d&&(f.cloneCsn=d),a?jp("screenCreated",f,a,e):kk("screenCreated",f,e);Wl(Zl,new Fs(k));return k}
function Ls(a,b,c,d){var e=d.filter(function(k){k.csn!==b?(k.csn=b,k=!0):k=!1;return k}),f={cttAuthInfo:gq(b),
X:b};d=p(d);for(var g=d.next();!g.done;g=d.next())g=g.value.getAsJson(),(pb(g)||!g.trackingParams&&!g.veType)&&Np(Error("Child VE logged with no data"));if(M("il_via_jspb")){var h=new lh;h.S(b);nh(h,c.getAsJspb());hb(e,function(k){k=k.getAsJspb();od(h,3,fh,k)});
"UNDEFINED_CSN"==b?Ms("visualElementAttached",h,f):Ep(h,f,a)}else c={csn:b,parentVe:c.getAsJson(),childVes:hb(e,function(k){return k.getAsJson()})},"UNDEFINED_CSN"==b?Ms("visualElementAttached",c,f):a?jp("visualElementAttached",c,a,f):kk("visualElementAttached",c,f)}
function Hs(){for(var a=Math.random()+"",b=[],c=0,d=0;d<a.length;d++){var e=a.charCodeAt(d);255<e&&(b[c++]=e&255,e>>=8);b[c++]=e}return Lc(b,3)}
function Ms(a,b,c){Gs.push({payloadName:a,payload:b,options:c});Js||(Js=$l())}
function am(a){if(Gs){for(var b=p(Gs),c=b.next();!c.done;c=b.next()){var d=c.value;if(d.payload)if(M("il_via_jspb"))switch(d.payload.S(a.csn),d.payloadName){case "screenCreated":Dp(d.payload,d.options);break;case "visualElementAttached":Ep(d.payload,d.options);break;case "visualElementShown":c=d.payload;d=d.options;var e=new Ah;nd(e,72,Bh,c);zp(e,d);break;case "visualElementHidden":Ap(d.payload,d.options);break;case "visualElementGestured":Bp(d.payload,d.options);break;case "visualElementStateChanged":Cp(d.payload,
d.options);break;default:Np(new Q("flushQueue unable to map payloadName to JSPB setter"))}else d.payload.csn=a.csn,jp(d.payloadName,d.payload,null,d.options)}Gs.length=0}Js=0}
;function Ns(){this.i=new Set;this.h=new Set;this.j=new Map}
Ns.prototype.clear=function(){this.i.clear();this.h.clear();this.j.clear()};
Na(Ns);function Os(){this.o=[];this.C=[];this.h=[];this.l=[];this.m=[];this.i=new Set;this.u=new Map}
function Ps(a,b,c){c=void 0===c?0:c;b.then(function(d){a.i.has(c)&&a.j&&a.j();var e=eq(c),f=cq(c);if(e&&f){var g;(null==d?0:null==(g=d.response)?0:g.trackingParams)&&Ls(a.client,e,f,[Zp(d.response.trackingParams)]);var h;(null==d?0:null==(h=d.playerResponse)?0:h.trackingParams)&&Ls(a.client,e,f,[Zp(d.playerResponse.trackingParams)])}})}
function Qs(a,b,c,d){d=void 0===d?0:d;if(a.i.has(d))a.o.push([b,c]);else{var e=eq(d);c=c||cq(d);e&&c&&Ls(a.client,e,c,[b])}}
Os.prototype.clickCommand=function(a,b,c){var d=a.clickTrackingParams;c=void 0===c?0:c;if(d)if(c=eq(void 0===c?0:c)){a=this.client;var e=Zp(d);var f="INTERACTION_LOGGING_GESTURE_TYPE_GENERIC_CLICK";d={cttAuthInfo:gq(c),X:c};if(M("il_via_jspb")){var g=new oh;g.S(c);e=e.getAsJspb();H(g,2,e);D(g,4,Ch[f]);b&&H(g,3);"UNDEFINED_CSN"==c?Ms("visualElementGestured",g,d):Bp(g,d,a)}else f={csn:c,ve:e.getAsJson(),gestureType:f},b&&(f.clientData=b),"UNDEFINED_CSN"==c?Ms("visualElementGestured",f,d):a?jp("visualElementGestured",
f,a,d):kk("visualElementGestured",f,d);b=!0}else b=!1;else b=!1;return b};
function Rs(a,b,c){c=void 0===c?{}:c;a.i.add(c.layer||0);a.j=function(){Ss(a,b,c);var f=cq(c.layer);if(f){for(var g=p(a.o),h=g.next();!h.done;h=g.next())h=h.value,Qs(a,h[0],h[1]||f,c.layer);f=p(a.C);for(g=f.next();!g.done;g=f.next()){var k=g.value;g=void 0;g=void 0===g?0:g;h=eq(g);var m=k[0]||cq(g);if(h&&m){g=a.client;var q=k[1];k={cttAuthInfo:gq(h),X:h};M("il_via_jspb")?(q=new qh,q.S(h),m=m.getAsJspb(),H(q,2,m),"UNDEFINED_CSN"==h?Ms("visualElementStateChanged",q,k):Cp(q,k,g)):(m={csn:h,ve:m.getAsJson(),
clientData:q},"UNDEFINED_CSN"==h?Ms("visualElementStateChanged",m,k):g?jp("visualElementStateChanged",m,g,k):kk("visualElementStateChanged",m,k))}}}};
eq(c.layer)||a.j();if(c.rb)for(var d=p(c.rb),e=d.next();!e.done;e=d.next())Ps(a,e.value,c.layer);else Mp(Error("Delayed screen needs a data promise."))}
function Ss(a,b,c){c=void 0===c?{}:c;c.layer||(c.layer=0);var d=void 0!==c.dc?c.dc:c.layer;var e=eq(d);d=cq(d);var f;d&&(void 0!==c.parentCsn?f={clientScreenNonce:c.parentCsn,visualElement:d}:e&&"UNDEFINED_CSN"!==e&&(f={clientScreenNonce:e,visualElement:d}));var g,h=A("EVENT_ID");"UNDEFINED_CSN"===e&&h&&(g={servletData:{serializedServletEventId:h}});try{var k=Ks(a.client,b,f,c.qb,c.cttAuthInfo,g,c.Ro)}catch(m){Pp(m,{Xo:b,rootVe:d,parentVisualElement:void 0,Oo:e,To:f,qb:c.qb});Mp(m);return}hq(k,b,
c.layer,c.cttAuthInfo);if(b=e&&"UNDEFINED_CSN"!==e&&d){a:{b=p(Object.values(Xp));for(f=b.next();!f.done;f=b.next())if(eq(f.value)===e){b=!0;break a}b=!1}b=!b}b&&(b=a.client,g=!0,h=(g=void 0===g?!1:g)?16:8,f={cttAuthInfo:gq(e),X:e,tb:g},M("il_via_jspb")?(h=new ph,h.S(e),d=d.getAsJspb(),H(h,2,d),D(h,4,g?16:8),"UNDEFINED_CSN"==e?Ms("visualElementHidden",h,f):Ap(h,f,b)):(d={csn:e,ve:d.getAsJson(),eventType:h},"UNDEFINED_CSN"==e?Ms("visualElementHidden",d,f):b?jp("visualElementHidden",d,b,f):kk("visualElementHidden",
d,f)));a.h[a.h.length-1]&&!a.h[a.h.length-1].csn&&(a.h[a.h.length-1].csn=k||"");$r({clientScreenNonce:k});Ns.getInstance().clear();d=cq(c.layer);e&&"UNDEFINED_CSN"!==e&&d&&(M("web_mark_root_visible")||M("music_web_mark_root_visible"))&&(e={cttAuthInfo:gq(k),X:k},M("il_via_jspb")?(b=new ph,b.S(k),f=d.getAsJspb(),H(b,2,f),D(b,4,1),"UNDEFINED_CSN"==k?Ms("visualElementShown",b,e):(k=new Ah,nd(k,72,Bh,b),zp(k,e))):(b={csn:k,ve:d.getAsJson(),eventType:1},"UNDEFINED_CSN"==k?Ms("visualElementShown",b,e):
kk("visualElementShown",b,e)));a.i.delete(c.layer||0);a.j=void 0;e=p(a.u);for(k=e.next();!k.done;k=e.next())b=p(k.value),k=b.next().value,b=b.next().value,b.has(c.layer)&&d&&Qs(a,k,d,c.layer);for(c=0;c<a.l.length;c++){e=a.l[c];try{e()}catch(m){Mp(m)}}for(c=a.l.length=0;c<a.m.length;c++){e=a.m[c];try{e()}catch(m){Mp(m)}}}
;function Ts(){var a,b;return w(function(c){if(1==c.h)return a=ks.h,a?t(c,ms(a),2):(Np(Error("InnertubeTransportService unavailable in fetchDatasyncIds")),c.return(void 0));if(b=c.i)return b.errorMetadata?(Mp(Error("Datasync IDs fetch responded with "+b.errorMetadata.code+": "+b.error)),c.return(void 0)):c.return(b.Po);Np(Error("Network request to get Datasync IDs failed."));return c.return(void 0)})}
;var Us=x.caches,Vs;function Ws(a){var b=a.indexOf(":");return-1===b?{Bb:a}:{Bb:a.substring(0,b),datasyncId:a.substring(b+1)}}
function Xs(){return w(function(a){if(void 0!==Vs)return a.return(Vs);Vs=new Promise(function(b){var c;return w(function(d){switch(d.h){case 1:return wa(d,2),t(d,Us.open("test-only"),4);case 4:return t(d,Us.delete("test-only"),5);case 5:xa(d,3);break;case 2:if(c=ya(d),c instanceof Error&&"SecurityError"===c.name)return b(!1),d.return();case 3:b("caches"in window),d.h=0}})});
return a.return(Vs)})}
function Ys(a){var b,c,d,e,f,g,h;w(function(k){if(1==k.h)return t(k,Xs(),2);if(3!=k.h){if(!k.i)return k.return(!1);b=[];return t(k,Us.keys(),3)}c=k.i;d=p(c);for(e=d.next();!e.done;e=d.next())f=e.value,g=Ws(f),h=g.datasyncId,!h||a.includes(h)||b.push(Us.delete(f));return k.return(Promise.all(b).then(function(m){return m.some(function(q){return q})}))})}
function Zs(){var a,b,c,d,e,f,g;return w(function(h){if(1==h.h)return t(h,Xs(),2);if(3!=h.h){if(!h.i)return h.return(!1);a=ok("cache contains other");return t(h,Us.keys(),3)}b=h.i;c=p(b);for(d=c.next();!d.done;d=c.next())if(e=d.value,f=Ws(e),(g=f.datasyncId)&&g!==a)return h.return(!0);return h.return(!1)})}
;function $s(){try{return!!self.localStorage}catch(a){return!1}}
;function at(a){a=a.match(/(.*)::.*::.*/);if(null!==a)return a[1]}
function bt(a){if($s()){var b=Object.keys(window.localStorage);b=p(b);for(var c=b.next();!c.done;c=b.next()){c=c.value;var d=at(c);void 0===d||a.includes(d)||self.localStorage.removeItem(c)}}}
function ct(){if(!$s())return!1;var a=ok(),b=Object.keys(window.localStorage);b=p(b);for(var c=b.next();!c.done;c=b.next())if(c=at(c.value),void 0!==c&&c!==a)return!0;return!1}
;function dt(){Ts().then(function(a){a&&(yl(a),Ys(a),bt(a))})}
function et(){var a=new Lm;bf.N(function(){var b,c,d,e;return w(function(f){switch(f.h){case 1:if(M("ytidb_clear_optimizations_killswitch")){f.s(2);break}b=ok("clear");if(b.startsWith("V")){var g=[b];yl(g);Ys(g);bt(g);return f.return()}c=ct();return t(f,Zs(),3);case 3:return d=f.i,t(f,zl(),4);case 4:if(e=f.i,!c&&!d&&!e)return f.return();case 2:a.H()?dt():a.l.add("publicytnetworkstatus-online",dt,!0,void 0,void 0),f.h=0}})})}
;function ft(a){a&&(a.dataset?a.dataset[gt("loaded")]="true":a.setAttribute("data-loaded","true"))}
function ht(a,b){return a?a.dataset?a.dataset[gt(b)]:a.getAttribute("data-"+b):null}
var jt={};function gt(a){return jt[a]||(jt[a]=String(a).replace(/\-([a-z])/g,function(b,c){return c.toUpperCase()}))}
;var kt=/\.vflset|-vfl[a-zA-Z0-9_+=-]+/,lt=/-[a-zA-Z]{2,3}_[a-zA-Z]{2,3}(?=(\/|$))/;function mt(a,b,c){c=void 0===c?null:c;if(window.spf&&spf.script){c="";if(a){var d=a.indexOf("jsbin/"),e=a.lastIndexOf(".js"),f=d+6;-1<d&&-1<e&&e>f&&(c=a.substring(f,e),c=c.replace(kt,""),c=c.replace(lt,""),c=c.replace("debug-",""),c=c.replace("tracing-",""))}spf.script.load(a,c,b)}else nt(a,b,c)}
function nt(a,b,c){c=void 0===c?null:c;var d=ot(a),e=document.getElementById(d),f=e&&ht(e,"loaded"),g=e&&!f;f?b&&b():(b&&(f=Mn(d,b),b=""+Sa(b),pt[b]=f),g||(e=qt(a,d,function(){ht(e,"loaded")||(ft(e),Pn(d),zi(Ya(Qn,d),0))},c)))}
function qt(a,b,c,d){d=void 0===d?null:d;var e=Ld("SCRIPT");e.id=b;e.onload=function(){c&&setTimeout(c,0)};
e.onreadystatechange=function(){switch(e.readyState){case "loaded":case "complete":e.onload()}};
d&&e.setAttribute("nonce",d);Hd(e,Lb(a));a=document.getElementsByTagName("head")[0]||document.body;a.insertBefore(e,a.firstChild);return e}
function rt(a){a=ot(a);var b=document.getElementById(a);b&&(Qn(a),b.parentNode.removeChild(b))}
function st(a,b){a&&b&&(a=""+Sa(b),(a=pt[a])&&On(a))}
function ot(a){var b=document.createElement("a");Vb(b,a);a=b.href.replace(/^[a-zA-Z]+:\/\//,"//");return"js-"+$b(a)}
var pt={};var tt=[],ut=!1;function vt(){if(!M("disable_biscotti_fetch_for_ad_blocker_detection")&&!M("disable_biscotti_fetch_entirely_for_all_web_clients")&&sq()&&"1"!=tb()){var a=function(){ut=!0;"google_ad_status"in window?Xh("DCLKSTAT",1):Xh("DCLKSTAT",2)};
try{mt("//static.doubleclick.net/instream/ad_status.js",a)}catch(b){}tt.push(bf.N(function(){if(!(ut||"google_ad_status"in window)){try{st("//static.doubleclick.net/instream/ad_status.js",a)}catch(b){}ut=!0;Xh("DCLKSTAT",3)}},5E3))}}
function wt(){var a=Number(A("DCLKSTAT",0));return isNaN(a)?0:a}
;function xt(){this.state=1;this.h=null}
l=xt.prototype;
l.initialize=function(a,b,c){if(a.program){var d,e=null!=(d=a.interpreterScript)?d:null,f;d=null!=(f=a.interpreterUrl)?f:null;a.interpreterSafeScript&&(e=a.interpreterSafeScript,Db("From proto message. b/166824318"),e=e.privateDoNotAccessOrElseSafeScriptWrappedValue||"",e=(f=Ab())?f.createScript(e):e,e=(new Fb(e)).toString());a.interpreterSafeUrl&&(d=a.interpreterSafeUrl,Db("From proto message. b/166824318"),d=Lb(d.privateDoNotAccessOrElseTrustedResourceUrlWrappedValue||"").toString());zt(this,e,
d,a.program,b,c)}else Np(Error("Cannot initialize botguard without program"))};
function zt(a,b,c,d,e,f){var g=void 0===g?"trayride":g;c?(a.state=2,mt(c,function(){window[g]?Ct(a,d,g,e):(a.state=3,rt(c),Np(new Q("Unable to load Botguard","from "+c)))},f)):b?(f=Ld("SCRIPT"),f.textContent=b,f.nonce=Yb(),document.head.appendChild(f),document.head.removeChild(f),window[g]?Ct(a,d,g,e):(a.state=4,Np(new Q("Unable to load Botguard from JS")))):Np(new Q("Unable to load VM; no url or JS provided"))}
l.isInitialized=function(){return!!this.h};
l.getState=function(){return this.state};
function Ct(a,b,c,d){a.state=5;try{var e=new Ad({program:b,globalName:c});e.vc.then(function(){a.state=6;d&&d(b)});
Dt(a,e)}catch(f){a.state=7,f instanceof Error&&Np(f)}}
l.invoke=function(a){a=void 0===a?{}:a;if(this.h){var b=this.h;a={pb:a};if(b.i)throw Error("Already disposed");b=b.l([a.pb,a.xc])}else b=null;return b};
l.dispose=function(){Dt(this,null);this.state=8};
function Dt(a,b){pe(a.h);a.h=b}
;var Et=new xt;function Ft(){return Et.isInitialized()}
function Gt(a){a=void 0===a?{}:a;return Et.invoke(a)}
;function Ht(a){var b=this;var c=void 0===c?0:c;var d=void 0===d?Zj():d;this.l=c;this.j=d;this.i=new zd;this.h=a;a={};c=p(this.h.entries());for(d=c.next();!d.done;a={sa:a.sa,Ba:a.Ba},d=c.next()){var e=p(d.value);d=e.next().value;e=e.next().value;a.Ba=d;a.sa=e;d=function(f){return function(){f.sa.eb();b.h[f.Ba].Ra=!0;b.h.every(function(g){return!0===g.Ra})&&b.i.resolve()}}(a);
e=Vj(d,It(this,a.sa));this.h[a.Ba]=Object.assign({},a.sa,{eb:d,Na:e})}}
function Jt(a){var b=Array.from(a.h.keys()).sort(function(d,e){return It(a,a.h[e])-It(a,a.h[d])});
b=p(b);for(var c=b.next();!c.done;c=b.next())c=a.h[c.value],void 0===c.Na||c.Ra||(a.j.U(c.Na),Vj(c.eb,10))}
Ht.prototype.cancel=function(){for(var a=p(this.h),b=a.next();!b.done;b=a.next())b=b.value,void 0===b.Na||b.Ra||this.j.U(b.Na),b.Ra=!0;this.i.resolve()};
function It(a,b){var c;return null!=(c=b.priority)?c:a.l}
;function Kt(a){this.state=a;this.plugins=[];this.m=void 0}
Kt.prototype.install=function(){this.plugins.push.apply(this.plugins,fa(Ja.apply(0,arguments)))};
Kt.prototype.transition=function(a,b){var c=this,d=this.C.find(function(f){return f.from===c.state&&f.B===a});
if(d){this.j&&(Jt(this.j),this.j=void 0);this.state=a;d=d.action.bind(this);var e=this.plugins.filter(function(f){return f[a]}).map(function(f){return f[a]});
d(Lt(this,e,this.m),b)}else throw Error("no transition specified from "+this.state+" to "+a);};
function Lt(a,b,c){return function(){var d=Ja.apply(0,arguments),e=b.filter(function(k){var m;return 10===(null!=(m=null!=c?c:k.priority)?m:0)}),f=b.filter(function(k){var m;
return 10!==(null!=(m=null!=c?c:k.priority)?m:0)});
Zj();var g={};e=p(e);for(var h=e.next();!h.done;g={Ca:g.Ca},h=e.next())g.Ca=h.value,Xj(function(k){return function(){k.Ca.ka.apply(k.Ca,fa(d))}}(g));
f=f.map(function(k){var m;return{eb:function(){k.ka.apply(k,fa(d))},
priority:null!=(m=null!=c?c:k.priority)?m:0}});
f.length&&(a.j=new Ht(f))}}
da.Object.defineProperties(Kt.prototype,{currentState:{configurable:!0,enumerable:!0,get:function(){return this.state}}});function Mt(a){Kt.call(this,void 0===a?"document_active":a);var b=this;this.m=10;this.h=new Map;this.C=[{from:"document_active",B:"document_disposed_preventable",action:this.u},{from:"document_active",B:"document_disposed",action:this.l},{from:"document_disposed_preventable",B:"document_disposed",action:this.l},{from:"document_disposed_preventable",B:"flush_logs",action:this.o},{from:"document_disposed_preventable",B:"document_active",action:this.i},{from:"document_disposed",B:"flush_logs",action:this.o},
{from:"document_disposed",B:"document_active",action:this.i},{from:"document_disposed",B:"document_disposed",action:function(){}},
{from:"flush_logs",B:"document_active",action:this.i}];window.addEventListener("pagehide",function(c){b.transition("document_disposed",{event:c})});
window.addEventListener("beforeunload",function(c){b.transition("document_disposed_preventable",{event:c})})}
r(Mt,Kt);Mt.prototype.u=function(a,b){if(!this.h.get("document_disposed_preventable")){a(null==b?void 0:b.event);var c,d;if((null==b?0:null==(c=b.event)?0:c.defaultPrevented)||(null==b?0:null==(d=b.event)?0:d.returnValue)){b.event.returnValue||(b.event.returnValue=!0);b.event.defaultPrevented||b.event.preventDefault();this.h=new Map;this.transition("document_active");return}}this.h.set("document_disposed_preventable",!0);this.h.get("document_disposed")?this.transition("flush_logs"):this.transition("document_disposed")};
Mt.prototype.l=function(a,b){this.h.get("document_disposed")?this.transition("document_active"):(a(null==b?void 0:b.event),this.h.set("document_disposed",!0),this.transition("flush_logs"))};
Mt.prototype.o=function(a,b){a(null==b?void 0:b.event);this.transition("document_active")};
Mt.prototype.i=function(){this.h=new Map};function Nt(a){Kt.call(this,void 0===a?"document_visibility_unknown":a);var b=this;this.C=[{from:"document_visibility_unknown",B:"document_visible",action:this.i},{from:"document_visibility_unknown",B:"document_hidden",action:this.h},{from:"document_visibility_unknown",B:"document_foregrounded",action:this.o},{from:"document_visibility_unknown",B:"document_backgrounded",action:this.l},{from:"document_visible",B:"document_hidden",action:this.h},{from:"document_visible",B:"document_foregrounded",action:this.o},
{from:"document_visible",B:"document_visible",action:this.i},{from:"document_foregrounded",B:"document_visible",action:this.i},{from:"document_foregrounded",B:"document_hidden",action:this.h},{from:"document_foregrounded",B:"document_foregrounded",action:this.o},{from:"document_hidden",B:"document_visible",action:this.i},{from:"document_hidden",B:"document_backgrounded",action:this.l},{from:"document_hidden",B:"document_hidden",action:this.h},{from:"document_backgrounded",B:"document_hidden",action:this.h},
{from:"document_backgrounded",B:"document_backgrounded",action:this.l},{from:"document_backgrounded",B:"document_visible",action:this.i}];document.addEventListener("visibilitychange",function(c){"visible"===document.visibilityState?b.transition("document_visible",{event:c}):b.transition("document_hidden",{event:c})});
M("visibility_lifecycles_dynamic_backgrounding")&&(window.addEventListener("blur",function(c){b.transition("document_backgrounded",{event:c})}),window.addEventListener("focus",function(c){b.transition("document_foregrounded",{event:c})}))}
r(Nt,Kt);Nt.prototype.i=function(a,b){a(null==b?void 0:b.event);M("visibility_lifecycles_dynamic_backgrounding")&&this.transition("document_foregrounded")};
Nt.prototype.h=function(a,b){a(null==b?void 0:b.event);M("visibility_lifecycles_dynamic_backgrounding")&&this.transition("document_backgrounded")};
Nt.prototype.l=function(a,b){a(null==b?void 0:b.event)};
Nt.prototype.o=function(a,b){a(null==b?void 0:b.event)};function Ot(){this.h=new Mt;this.i=new Nt}
Ot.prototype.install=function(){var a=Ja.apply(0,arguments);this.h.install.apply(this.h,fa(a));this.i.install.apply(this.i,fa(a))};function Pt(){Ot.call(this);var a={};this.install((a.document_disposed={ka:this.j},a));a={};this.install((a.flush_logs={ka:this.l},a))}
var Qt;r(Pt,Ot);Pt.prototype.l=function(){if(M("web_fp_via_jspb")){var a=new eh,b=eq();b&&a.S(b);b=new Ah;nd(b,380,Bh,a);zp(b);M("web_fp_via_jspb_and_json")&&kk("finalPayload",{csn:eq()})}else kk("finalPayload",{csn:eq()})};
Pt.prototype.j=function(){Rp(Sp)};function Rt(){}
Rt.getInstance=function(){var a=z("ytglobal.storage_");a||(a=new Rt,y("ytglobal.storage_",a));return a};
Rt.prototype.estimate=function(){var a,b,c;return w(function(d){a=navigator;return(null==(b=a.storage)?0:b.estimate)?d.return(a.storage.estimate()):(null==(c=a.webkitTemporaryStorage)?0:c.queryUsageAndQuota)?d.return(St()):d.return()})};
function St(){var a=navigator;return new Promise(function(b,c){var d;null!=(d=a.webkitTemporaryStorage)&&d.queryUsageAndQuota?a.webkitTemporaryStorage.queryUsageAndQuota(function(e,f){b({usage:e,quota:f})},function(e){c(e)}):c(Error("webkitTemporaryStorage is not supported."))})}
y("ytglobal.storageClass_",Rt);function ik(a,b){var c=this;this.handleError=a;this.h=b;this.i=!1;void 0===self.document||self.addEventListener("beforeunload",function(){c.i=!0});
this.j=Math.random()<=$h("ytidb_transaction_ended_event_rate_limit",.02)}
ik.prototype.logEvent=function(a,b){switch(a){case "IDB_DATA_CORRUPTED":M("idb_data_corrupted_killswitch")||this.h("idbDataCorrupted",b);break;case "IDB_UNEXPECTEDLY_CLOSED":this.h("idbUnexpectedlyClosed",b);break;case "IS_SUPPORTED_COMPLETED":M("idb_is_supported_completed_killswitch")||this.h("idbIsSupportedCompleted",b);break;case "QUOTA_EXCEEDED":Tt(this,b);break;case "TRANSACTION_ENDED":this.j&&this.h("idbTransactionEnded",b);break;case "TRANSACTION_UNEXPECTEDLY_ABORTED":a=Object.assign({},b,
{hasWindowUnloaded:this.i}),this.h("idbTransactionAborted",a)}};
function Tt(a,b){Rt.getInstance().estimate().then(function(c){c=Object.assign({},b,{isSw:void 0===self.document,isIframe:self!==self.top,deviceStorageUsageMbytes:Ut(null==c?void 0:c.usage),deviceStorageQuotaMbytes:Ut(null==c?void 0:c.quota)});a.h("idbQuotaExceeded",c)})}
function Ut(a){return"undefined"===typeof a?"-1":String(Math.ceil(a/1048576))}
;var Vt=window;
function Wt(){var a=Vt.uaChPolyfill.state;if(0===a.type)kk("clientHintsPolyfillEvent",{clientHintsSupported:!1});else{var b=navigator.userAgent,c=void 0!==a.syntheticUa&&a.syntheticUa===b,d={clientHintsSupported:!0,uaAccessedBeforePolyfill:a.didAccessUaBeforePolyfillAvailable,syntheticUaMatches:c};a.didAccessUaBeforePolyfillAvailable&&(d.uaAccessBeforePolyfillCount=a.uaAccessBeforePolyfillCount,a.firstAccessUaError&&(d.firstUaAccessStack=String(a.firstAccessUaError.stack).replace(/\n/g,""),Mp(a.firstAccessUaError)),
d.polyfillAvailabilityDelayMs=a.polyfillAvailabilityDelay);kk("clientHintsPolyfillEvent",d);c||(b={syntheticUa:a.syntheticUa,ua:b},b.brand=a.data.brands.map(function(e){return'"'+e.brand+'"; v="'+e.version+'"'}),b.mobileness=a.data.mobile,a=a.data.values,a.architecture&&(b.platformArchitecture=a.architecture),a.model&&(b.model=a.model),a.platform&&(b.platformBrand=a.platform),a.platformVersion&&(b.platformVersion=a.platformVersion),a.uaFullVersion&&(b.fullVersion=a.uaFullVersion),kk("clientHintsPolyfillDiagnostics",
b))}}
var Xt=!1;function Yt(){var a;1===(null==(a=Vt.uaChPolyfill)?void 0:a.state.type)?Xt||(Vt.uaChPolyfill.onReady=Yt,Xt=!0):Vt.uaChPolyfill&&Wt()}
;function Zt(a,b,c){K.call(this);var d=this;c=c||A("POST_MESSAGE_ORIGIN")||window.document.location.protocol+"//"+window.document.location.hostname;this.j=b||null;this.L="*";this.l=c;this.sessionId=null;this.channel="widget";this.M=!!a;this.A=function(e){a:if(!("*"!=d.l&&e.origin!=d.l||d.j&&e.source!=d.j||"string"!==typeof e.data)){try{var f=JSON.parse(e.data)}catch(g){break a}if(!(null==f||d.M&&(d.sessionId&&d.sessionId!=f.id||d.channel&&d.channel!=f.channel))&&f)switch(f.event){case "listening":"null"!=
e.origin&&(d.l=d.L=e.origin);d.j=e.source;d.sessionId=f.id;d.i&&(d.i(),d.i=null);break;case "command":d.m&&(!d.u||0<=eb(d.u,f.func))&&d.m(f.func,f.args,e.origin)}}};
this.u=this.i=this.m=null;window.addEventListener("message",this.A)}
r(Zt,K);Zt.prototype.sendMessage=function(a,b){if(b=b||this.j){this.sessionId&&(a.id=this.sessionId);this.channel&&(a.channel=this.channel);try{var c=JSON.stringify(a);b.postMessage(c,this.L)}catch(d){gi(d)}}};
Zt.prototype.I=function(){window.removeEventListener("message",this.A);K.prototype.I.call(this)};function $t(){this.i=[];this.isReady=!1;this.j={};var a=this.h=new Zt(!!A("WIDGET_ID_ENFORCE")),b=this.hc.bind(this);a.m=b;a.u=null;this.h.channel="widget";if(a=A("WIDGET_ID"))this.h.sessionId=a}
l=$t.prototype;l.hc=function(a,b,c){"addEventListener"===a&&b?(a=b[0],this.j[a]||"onReady"===a||(this.addEventListener(a,au(this,a)),this.j[a]=!0)):this.kb(a,b,c)};
l.kb=function(){};
function au(a,b){return function(c){return a.sendMessage(b,c)}}
l.addEventListener=function(){};
l.Ub=function(){this.isReady=!0;this.sendMessage("initialDelivery",this.Xa());this.sendMessage("onReady");fb(this.i,this.Hb,this);this.i=[]};
l.Xa=function(){return null};
function bu(a,b){a.sendMessage("infoDelivery",b)}
l.Hb=function(a){this.isReady?this.h.sendMessage(a):this.i.push(a)};
l.sendMessage=function(a,b){this.Hb({event:a,info:void 0===b?null:b})};
l.dispose=function(){this.h=null};function cu(a){return(0===a.search("cue")||0===a.search("load"))&&"loadModule"!==a}
function du(a,b,c){if("string"===typeof a)return{videoId:a,startSeconds:b,suggestedQuality:c};b=["endSeconds","startSeconds","mediaContentUrl","suggestedQuality","videoId"];c={};for(var d=0;d<b.length;d++){var e=b[d];a[e]&&(c[e]=a[e])}return c}
function eu(a,b,c,d){if(Ra(a)&&!Array.isArray(a)){b="playlist list listType index startSeconds suggestedQuality".split(" ");c={};for(d=0;d<b.length;d++){var e=b[d];a[e]&&(c[e]=a[e])}return c}b={index:b,startSeconds:c,suggestedQuality:d};"string"===typeof a&&16===a.length?b.list="PL"+a:b.playlist=a;return b}
;function fu(a){$t.call(this);this.listeners=[];this.api=a;this.addEventListener("onReady",this.onReady.bind(this));this.addEventListener("onVideoProgress",this.sc.bind(this));this.addEventListener("onVolumeChange",this.tc.bind(this));this.addEventListener("onApiChange",this.lc.bind(this));this.addEventListener("onPlaybackQualityChange",this.oc.bind(this));this.addEventListener("onPlaybackRateChange",this.pc.bind(this));this.addEventListener("onStateChange",this.qc.bind(this));this.addEventListener("onWebglSettingsChanged",
this.uc.bind(this))}
r(fu,$t);l=fu.prototype;
l.kb=function(a,b,c){if(this.api.isExternalMethodAvailable(a,c)){b=b||[];if(0<b.length&&cu(a)){var d=b;if(Ra(d[0])&&!Array.isArray(d[0]))var e=d[0];else switch(e={},a){case "loadVideoById":case "cueVideoById":e=du(d[0],void 0!==d[1]?Number(d[1]):void 0,d[2]);break;case "loadVideoByUrl":case "cueVideoByUrl":e=d[0];"string"===typeof e&&(e={mediaContentUrl:e,startSeconds:void 0!==d[1]?Number(d[1]):void 0,suggestedQuality:d[2]});b:{if((d=e.mediaContentUrl)&&(d=/\/([ve]|embed)\/([^#?]+)/.exec(d))&&d[2]){d=
d[2];break b}d=null}e.videoId=d;e=du(e);break;case "loadPlaylist":case "cuePlaylist":e=eu(d[0],d[1],d[2],d[3])}b.length=1;b[0]=e}this.api.handleExternalCall(a,b,c);cu(a)&&bu(this,this.Xa())}};
l.onReady=function(){var a=this.Ub.bind(this);this.h.i=a};
l.addEventListener=function(a,b){this.listeners.push({eventType:a,listener:b});this.api.addEventListener(a,b)};
l.Xa=function(){if(!this.api)return null;var a=this.api.getApiInterface();kb(a,"getVideoData");for(var b={apiInterface:a},c=0,d=a.length;c<d;c++){var e=a[c];if(0===e.search("get")||0===e.search("is")){var f=0;0===e.search("get")?f=3:0===e.search("is")&&(f=2);f=e.charAt(f).toLowerCase()+e.substr(f+1);try{var g=this.api[e]();b[f]=g}catch(h){}}}b.videoData=this.api.getVideoData();b.currentTimeLastUpdated_=Date.now()/1E3;return b};
l.qc=function(a){a={playerState:a,currentTime:this.api.getCurrentTime(),duration:this.api.getDuration(),videoData:this.api.getVideoData(),videoStartBytes:0,videoBytesTotal:this.api.getVideoBytesTotal(),videoLoadedFraction:this.api.getVideoLoadedFraction(),playbackQuality:this.api.getPlaybackQuality(),availableQualityLevels:this.api.getAvailableQualityLevels(),currentTimeLastUpdated_:Date.now()/1E3,playbackRate:this.api.getPlaybackRate(),mediaReferenceTime:this.api.getMediaReferenceTime()};this.api.getVideoUrl&&
(a.videoUrl=this.api.getVideoUrl());this.api.getVideoContentRect&&(a.videoContentRect=this.api.getVideoContentRect());this.api.getProgressState&&(a.progressState=this.api.getProgressState());this.api.getPlaylist&&(a.playlist=this.api.getPlaylist());this.api.getPlaylistIndex&&(a.playlistIndex=this.api.getPlaylistIndex());this.api.getStoryboardFormat&&(a.storyboardFormat=this.api.getStoryboardFormat());bu(this,a)};
l.oc=function(a){bu(this,{playbackQuality:a})};
l.pc=function(a){bu(this,{playbackRate:a})};
l.lc=function(){for(var a=this.api.getOptions(),b={namespaces:a},c=0,d=a.length;c<d;c++){var e=a[c],f=this.api.getOptions(e);b[e]={options:f};for(var g=0,h=f.length;g<h;g++){var k=f[g],m=this.api.getOption(e,k);b[e][k]=m}}this.sendMessage("apiInfoDelivery",b)};
l.tc=function(){bu(this,{muted:this.api.isMuted(),volume:this.api.getVolume()})};
l.sc=function(a){a={currentTime:a,videoBytesLoaded:this.api.getVideoBytesLoaded(),videoLoadedFraction:this.api.getVideoLoadedFraction(),currentTimeLastUpdated_:Date.now()/1E3,playbackRate:this.api.getPlaybackRate(),mediaReferenceTime:this.api.getMediaReferenceTime()};this.api.getProgressState&&(a.progressState=this.api.getProgressState());bu(this,a)};
l.uc=function(){var a={sphericalProperties:this.api.getSphericalProperties()};bu(this,a)};
l.dispose=function(){$t.prototype.dispose.call(this);for(var a=0;a<this.listeners.length;a++){var b=this.listeners[a];this.api.removeEventListener(b.eventType,b.listener)}this.listeners=[]};function gu(a){K.call(this);this.i={};this.started=!1;this.connection=a;this.connection.subscribe("command",this.Db,this)}
r(gu,K);l=gu.prototype;l.start=function(){this.started||this.h()||(this.started=!0,this.connection.la("RECEIVING"))};
l.la=function(a,b){this.started&&!this.h()&&this.connection.la(a,b)};
l.Db=function(a,b,c){if(this.started&&!this.h()){var d=b||{};switch(a){case "addEventListener":"string"===typeof d.event&&this.addListener(d.event);break;case "removeEventListener":"string"===typeof d.event&&this.removeListener(d.event);break;default:this.api.isReady()&&this.api.isExternalMethodAvailable(a,c||null)&&(b=hu(a,b||{}),c=this.api.handleExternalCall(a,b,c||null),(c=iu(a,c))&&this.la(a,c))}}};
l.addListener=function(a){if(!(a in this.i)){var b=this.mc.bind(this,a);this.i[a]=b;this.addEventListener(a,b)}};
l.mc=function(a,b){this.started&&!this.h()&&this.connection.la(a,this.Wa(a,b))};
l.Wa=function(a,b){if(null!=b)return{value:b}};
l.removeListener=function(a){a in this.i&&(this.removeEventListener(a,this.i[a]),delete this.i[a])};
l.I=function(){var a=this.connection;a.h()||og(a.i,"command",this.Db,this);this.connection=null;for(var b in this.i)this.i.hasOwnProperty(b)&&this.removeListener(b);K.prototype.I.call(this)};function ju(a,b){gu.call(this,b);this.api=a;this.start()}
r(ju,gu);ju.prototype.addEventListener=function(a,b){this.api.addEventListener(a,b)};
ju.prototype.removeEventListener=function(a,b){this.api.removeEventListener(a,b)};
function hu(a,b){switch(a){case "loadVideoById":return a=du(b),[a];case "cueVideoById":return a=du(b),[a];case "loadVideoByPlayerVars":return[b];case "cueVideoByPlayerVars":return[b];case "loadPlaylist":return a=eu(b),[a];case "cuePlaylist":return a=eu(b),[a];case "seekTo":return[b.seconds,b.allowSeekAhead];case "playVideoAt":return[b.index];case "setVolume":return[b.volume];case "setPlaybackQuality":return[b.suggestedQuality];case "setPlaybackRate":return[b.suggestedRate];case "setLoop":return[b.loopPlaylists];
case "setShuffle":return[b.shufflePlaylist];case "getOptions":return[b.module];case "getOption":return[b.module,b.option];case "setOption":return[b.module,b.option,b.value];case "handleGlobalKeyDown":return[b.keyCode,b.shiftKey,b.ctrlKey,b.altKey,b.metaKey,b.key,b.code]}return[]}
function iu(a,b){switch(a){case "isMuted":return{muted:b};case "getVolume":return{volume:b};case "getPlaybackRate":return{playbackRate:b};case "getAvailablePlaybackRates":return{availablePlaybackRates:b};case "getVideoLoadedFraction":return{videoLoadedFraction:b};case "getPlayerState":return{playerState:b};case "getCurrentTime":return{currentTime:b};case "getPlaybackQuality":return{playbackQuality:b};case "getAvailableQualityLevels":return{availableQualityLevels:b};case "getDuration":return{duration:b};
case "getVideoUrl":return{videoUrl:b};case "getVideoEmbedCode":return{videoEmbedCode:b};case "getPlaylist":return{playlist:b};case "getPlaylistIndex":return{playlistIndex:b};case "getOptions":return{options:b};case "getOption":return{option:b}}}
ju.prototype.Wa=function(a,b){switch(a){case "onReady":return;case "onStateChange":return{playerState:b};case "onPlaybackQualityChange":return{playbackQuality:b};case "onPlaybackRateChange":return{playbackRate:b};case "onError":return{errorCode:b}}return gu.prototype.Wa.call(this,a,b)};
ju.prototype.I=function(){gu.prototype.I.call(this);delete this.api};function ku(a){a=void 0===a?!1:a;K.call(this);this.i=new L(a);re(this,Ya(pe,this.i))}
Za(ku,K);ku.prototype.subscribe=function(a,b,c){return this.h()?0:this.i.subscribe(a,b,c)};
ku.prototype.l=function(a,b){this.h()||this.i.ja.apply(this.i,arguments)};function lu(a,b,c){ku.call(this);this.j=a;this.destination=b;this.id=c}
r(lu,ku);lu.prototype.la=function(a,b){this.h()||this.j.la(this.destination,this.id,a,b)};
lu.prototype.I=function(){this.destination=this.j=null;ku.prototype.I.call(this)};function mu(a,b,c){K.call(this);this.destination=a;this.origin=c;this.i=zn(window,"message",this.j.bind(this));this.connection=new lu(this,a,b);re(this,Ya(pe,this.connection))}
r(mu,K);mu.prototype.la=function(a,b,c,d){this.h()||a!==this.destination||(a={id:b,command:c},d&&(a.data=d),this.destination.postMessage(Qf(a),this.origin))};
mu.prototype.j=function(a){var b;if(b=!this.h())if(b=a.origin===this.origin)a:{b=this.destination;do{b:{var c=a.source;do{if(c===b){c=!0;break b}if(c===c.parent)break;c=c.parent}while(null!=c);c=!1}if(c){b=!0;break a}b=b.opener}while(null!=b);b=!1}if(b&&(b=a.data,"string"===typeof b)){try{b=JSON.parse(b)}catch(d){return}b.command&&(c=this.connection,c.h()||c.l("command",b.command,b.data,a.origin))}};
mu.prototype.I=function(){An(this.i);this.destination=null;K.prototype.I.call(this)};function nu(a){a=a||{};var b={},c={};this.url=a.url||"";this.args=a.args||vb(b);this.assets=a.assets||{};this.attrs=a.attrs||vb(c);this.fallback=a.fallback||null;this.fallbackMessage=a.fallbackMessage||null;this.html5=!!a.html5;this.disable=a.disable||{};this.loaded=!!a.loaded;this.messages=a.messages||{}}
nu.prototype.clone=function(){var a=new nu,b;for(b in this)if(this.hasOwnProperty(b)){var c=this[b];"object"==Pa(c)?a[b]=vb(c):a[b]=c}return a};var ou=/cssbin\/(?:debug-)?([a-zA-Z0-9_-]+?)(?:-2x|-web|-rtl|-vfl|.css)/;function pu(a){a=a||"";if(window.spf){var b=a.match(ou);spf.style.load(a,b?b[1]:"",void 0)}else qu(a)}
function qu(a){var b=ru(a),c=document.getElementById(b),d=c&&ht(c,"loaded");d||c&&!d||(c=su(a,b,function(){ht(c,"loaded")||(ft(c),Pn(b),zi(Ya(Qn,b),0))}))}
function su(a,b,c){var d=document.createElement("link");d.id=b;d.onload=function(){c&&setTimeout(c,0)};
a=Lb(a);Wb(d,a);(document.getElementsByTagName("head")[0]||document.body).appendChild(d);return d}
function ru(a){var b=Ld("A");Db("This URL is never added to the DOM");Vb(b,new Nb(a,Ob));a=b.href.replace(/^[a-zA-Z]+:\/\//,"//");return"css-"+$b(a)}
;function tu(){K.call(this);this.i=[]}
r(tu,K);tu.prototype.I=function(){for(;this.i.length;){var a=this.i.pop();a.target.removeEventListener(a.name,a.ka,void 0)}K.prototype.I.call(this)};function uu(){tu.apply(this,arguments)}
r(uu,tu);function vu(a,b,c,d){K.call(this);var e=this;this.M=b;this.webPlayerContextConfig=d;this.Ta=!1;this.api={};this.Da=this.u=null;this.T=new L;this.i={};this.fa=this.Ea=this.elementId=this.Ua=this.config=null;this.Y=!1;this.l=this.A=null;this.Fa={};this.Lb=["onReady"];this.lastError=null;this.lb=NaN;this.L={};this.Mb=new uu(this);this.na=0;this.j=this.m=a;re(this,Ya(pe,this.T));wu(this);xu(this);re(this,Ya(pe,this.Mb));c?this.na=zi(function(){e.loadNewVideoConfig(c)},0):d&&(yu(this),zu(this))}
r(vu,K);l=vu.prototype;l.getId=function(){return this.M};
l.loadNewVideoConfig=function(a){if(!this.h()){this.na&&(Ai(this.na),this.na=0);var b=a||{};b instanceof nu||(b=new nu(b));this.config=b;this.setConfig(a);zu(this);this.isReady()&&Au(this)}};
function yu(a){var b;a.webPlayerContextConfig?b=a.webPlayerContextConfig.rootElementId:b=a.config.attrs.id;a.elementId=b||a.elementId;"video-player"===a.elementId&&(a.elementId=a.M,a.webPlayerContextConfig?a.webPlayerContextConfig.rootElementId=a.M:a.config.attrs.id=a.M);var c;(null==(c=a.j)?void 0:c.id)===a.elementId&&(a.elementId+="-player",a.webPlayerContextConfig?a.webPlayerContextConfig.rootElementId=a.elementId:a.config.attrs.id=a.elementId)}
l.setConfig=function(a){this.Ua=a;this.config=Bu(a);yu(this);if(!this.Ea){var b;this.Ea=Cu(this,(null==(b=this.config.args)?void 0:b.jsapicallback)||"onYouTubePlayerReady")}this.config.args?this.config.args.jsapicallback=null:this.config.args={jsapicallback:null};var c;if(null==(c=this.config)?0:c.attrs)a=this.config.attrs,(b=a.width)&&this.j&&(this.j.style.width=Wd(Number(b)||b)),(a=a.height)&&this.j&&(this.j.style.height=Wd(Number(a)||a))};
function Au(a){if(a.config&&!0!==a.config.loaded)if(a.config.loaded=!0,!a.config.args||"0"!==a.config.args.autoplay&&0!==a.config.args.autoplay&&!1!==a.config.args.autoplay){var b;a.api.loadVideoByPlayerVars(null!=(b=a.config.args)?b:null)}else a.api.cueVideoByPlayerVars(a.config.args)}
function Du(a){var b=!0,c=Eu(a);c&&a.config&&(a=Fu(a),b=ht(c,"version")===a);return b&&!!z("yt.player.Application.create")}
function zu(a){if(!a.h()&&!a.Y){var b=Du(a);if(b&&"html5"===(Eu(a)?"html5":null))a.fa="html5",a.isReady()||Gu(a);else if(Hu(a),a.fa="html5",b&&a.l&&a.m)a.m.appendChild(a.l),Gu(a);else{a.config&&(a.config.loaded=!0);var c=!1;a.A=function(){c=!0;var d=Iu(a,"player_bootstrap_method")?z("yt.player.Application.createAlternate")||z("yt.player.Application.create"):z("yt.player.Application.create");var e=a.config?Bu(a.config):void 0;d&&d(a.m,e,a.webPlayerContextConfig);Gu(a)};
a.Y=!0;b?a.A():(mt(Fu(a),a.A),(b=Ju(a))&&pu(b),Ku(a)&&!c&&y("yt.player.Application.create",null))}}}
function Eu(a){var b=Kd(a.elementId);!b&&a.j&&a.j.querySelector&&(b=a.j.querySelector("#"+a.elementId));return b}
function Gu(a){if(!a.h()){var b=Eu(a),c=!1;b&&b.getApiInterface&&b.getApiInterface()&&(c=!0);if(c){a.Y=!1;if(!Iu(a,"html5_remove_not_servable_check_killswitch")){var d;if((null==b?0:b.isNotServable)&&a.config&&(null==b?0:b.isNotServable(null==(d=a.config.args)?void 0:d.video_id)))return}Lu(a)}else a.lb=zi(function(){Gu(a)},50)}}
function Lu(a){wu(a);a.Ta=!0;var b=Eu(a);if(b){a.u=Mu(a,b,"addEventListener");a.Da=Mu(a,b,"removeEventListener");var c=b.getApiInterface();c=c.concat(b.getInternalApiInterface());for(var d=a.api,e=0;e<c.length;e++){var f=c[e];d[f]||(d[f]=Mu(a,b,f))}}for(var g in a.i)a.i.hasOwnProperty(g)&&a.u&&a.u(g,a.i[g]);Au(a);a.Ea&&a.Ea(a.api);a.T.ja("onReady",a.api)}
function Mu(a,b,c){var d=b[c];return function(){var e=Ja.apply(0,arguments);try{return a.lastError=null,d.apply(b,e)}catch(f){"sendAbandonmentPing"!==c&&(f.params=c,a.lastError=f,Np(f))}}}
function wu(a){a.Ta=!1;if(a.Da)for(var b in a.i)a.i.hasOwnProperty(b)&&a.Da(b,a.i[b]);for(var c in a.L)a.L.hasOwnProperty(c)&&Ai(Number(c));a.L={};a.u=null;a.Da=null;b=a.api;for(var d in b)b.hasOwnProperty(d)&&(b[d]=null);b.addEventListener=function(e,f){a.addEventListener(e,f)};
b.removeEventListener=function(e,f){a.removeEventListener(e,f)};
b.destroy=function(){a.dispose()};
b.getLastError=function(){return a.getLastError()};
b.getPlayerType=function(){return a.getPlayerType()};
b.getCurrentVideoConfig=function(){return a.Ua};
b.loadNewVideoConfig=function(e){a.loadNewVideoConfig(e)};
b.isReady=function(){return a.isReady()}}
l.isReady=function(){return this.Ta};
function xu(a){a.addEventListener("WATCH_LATER_VIDEO_ADDED",function(b){Pn("WATCH_LATER_VIDEO_ADDED",b)});
a.addEventListener("WATCH_LATER_VIDEO_REMOVED",function(b){Pn("WATCH_LATER_VIDEO_REMOVED",b)})}
l.addEventListener=function(a,b){var c=this,d=Cu(this,b);d&&(0<=eb(this.Lb,a)||this.i[a]||(b=Nu(this,a),this.u&&this.u(a,b)),this.T.subscribe(a,d),"onReady"===a&&this.isReady()&&zi(function(){d(c.api)},0))};
l.removeEventListener=function(a,b){this.h()||(b=Cu(this,b))&&og(this.T,a,b)};
function Cu(a,b){var c=b;if("string"===typeof b){if(a.Fa[b])return a.Fa[b];c=function(){var d=Ja.apply(0,arguments),e=z(b);if(e)try{e.apply(x,d)}catch(f){Mp(f)}};
a.Fa[b]=c}return c?c:null}
function Nu(a,b){var c="ytPlayer"+b+a.M;a.i[b]=c;x[c]=function(d){var e=zi(function(){if(!a.h()){a.T.ja(b,null!=d?d:void 0);var f=a.L,g=String(e);g in f&&delete f[g]}},0);
sb(a.L,String(e))};
return c}
l.getPlayerType=function(){return this.fa||(Eu(this)?"html5":null)};
l.getLastError=function(){return this.lastError};
function Hu(a){a.cancel();wu(a);a.fa=null;a.config&&(a.config.loaded=!1);var b=Eu(a);b&&(Du(a)||!Ku(a)?a.l=b:(b&&b.destroy&&b.destroy(),a.l=null));if(a.m)for(a=a.m;b=a.firstChild;)a.removeChild(b)}
l.cancel=function(){this.A&&st(Fu(this),this.A);Ai(this.lb);this.Y=!1};
l.I=function(){Hu(this);if(this.l&&this.config&&this.l.destroy)try{this.l.destroy()}catch(b){Mp(b)}this.Fa=null;for(var a in this.i)this.i.hasOwnProperty(a)&&(x[this.i[a]]=null);this.Ua=this.config=this.api=null;delete this.m;delete this.j;K.prototype.I.call(this)};
function Ku(a){var b,c;a=null==(b=a.config)?void 0:null==(c=b.args)?void 0:c.fflags;return!!a&&-1!==a.indexOf("player_destroy_old_version=true")}
function Fu(a){return a.webPlayerContextConfig?a.webPlayerContextConfig.jsUrl:(a=a.config.assets)?a.js:""}
function Ju(a){return a.webPlayerContextConfig?a.webPlayerContextConfig.cssUrl:(a=a.config.assets)?a.css:""}
function Iu(a,b){if(a.webPlayerContextConfig)var c=a.webPlayerContextConfig.serializedExperimentFlags;else{var d;if(null==(d=a.config)?0:d.args)c=a.config.args.fflags}return"true"===mi(c||"","&")[b]}
function Bu(a){for(var b={},c=p(Object.keys(a)),d=c.next();!d.done;d=c.next()){d=d.value;var e=a[d];b[d]="object"===typeof e?vb(e):e}return b}
;var Ou={},Pu="player_uid_"+(1E9*Math.random()>>>0);function Qu(a,b,c){var d="player";c=void 0===c?!0:c;d="string"===typeof d?Kd(d):d;var e=Pu+"_"+Sa(d),f=Ou[e];if(f&&c)return Ru(a,b)?f.api.loadVideoByPlayerVars(a.args||null):f.loadNewVideoConfig(a),f.api;f=new vu(d,e,a,b);Ou[e]=f;Pn("player-added",f.api);re(f,function(){delete Ou[f.getId()]});
return f.api}
function Ru(a,b){return b&&b.serializedExperimentFlags?b.serializedExperimentFlags.includes("web_player_remove_playerproxy=true"):a&&a.args&&a.args.fflags?a.args.fflags.includes("web_player_remove_playerproxy=true"):!1}
;var Su=null,Tu=null,Uu=null;function Vu(){var a=Su.getVideoData(1);a=a.title?a.title+" - YouTube":"YouTube";document.title!==a&&(document.title=a)}
;function Wu(a,b,c){a="ST-"+$b(a).toString(36);b=b?gc(b):"";c=c||5;sq()&&lj(a,b,c)}
;function Xu(a,b,c){b=void 0===b?{}:b;c=void 0===c?!1:c;var d=A("EVENT_ID");d&&(b.ei||(b.ei=d));if(b){d=a;var e=void 0===e?!0:e;var f=A("VALID_SESSION_TEMPDATA_DOMAINS",[]),g=dc(window.location.href);g&&f.push(g);g=dc(d);if(0<=eb(f,g)||!g&&0==d.lastIndexOf("/",0))if(M("autoescape_tempdata_url")&&(f=document.createElement("a"),Vb(f,d),d=f.href),d&&(d=ec(d),f=d.indexOf("#"),d=0>f?d:d.substr(0,f)))if(e&&!b.csn&&(b.itct||b.ved)&&(b=Object.assign({csn:eq()},b)),h){var h=parseInt(h,10);isFinite(h)&&0<h&&
Wu(d,b,h)}else Wu(d,b)}if(c)return!1;if((window.ytspf||{}).enabled)spf.navigate(a);else{var k=void 0===k?{}:k;var m=void 0===m?"":m;var q=void 0===q?window:q;c=q.location;a=hc(a,k)+m;var u=void 0===u?Vd:u;a:{u=void 0===u?Vd:u;for(k=0;k<u.length;++k)if(m=u[k],m instanceof Td&&m.isValid(a)){u=new Ed(a,Cd);break a}u=void 0}c.href=Gd(u||Fd)}return!0}
;y("yt.setConfig",Xh);y("yt.config.set",Xh);y("yt.setMsg",jq);y("yt.msgs.set",jq);y("yt.logging.errors.log",Mp);
y("writeEmbed",function(){var a=A("PLAYER_CONFIG");if(!a){var b=A("PLAYER_VARS");b&&(a={args:b})}Aq(!0);"gvn"===a.args.ps&&(document.body.style.backgroundColor="transparent");a.attrs||(a.attrs={width:"100%",height:"100%",id:"video-player"});var c=document.referrer;b=A("POST_MESSAGE_ORIGIN");window!==window.top&&c&&c!==document.URL&&(a.args.loaderUrl=c);M("embeds_js_api_set_1p_cookie")&&(c=ri(window.location.href),c.embedsTokenValue&&(a.args.embedsTokenValue=c.embedsTokenValue));Yr();if((c=A("WEB_PLAYER_CONTEXT_CONFIGS"))&&
"WEB_PLAYER_CONTEXT_CONFIG_ID_EMBEDDED_PLAYER"in c){c=c.WEB_PLAYER_CONTEXT_CONFIG_ID_EMBEDDED_PLAYER;if(!c.serializedForcedExperimentIds){var d=ri(window.location.href);d.forced_experiments&&(c.serializedForcedExperimentIds=d.forced_experiments)}Su=Qu(a,c,!1)}else Su=Qu(a);Su.addEventListener("onVideoDataChange",Vu);a=A("POST_MESSAGE_ID","player");A("ENABLE_JS_API")?Uu=new fu(Su):A("ENABLE_POST_API")&&"string"===typeof a&&"string"===typeof b&&(Tu=new mu(window.parent,a,b),Uu=new ju(Su,Tu.connection));
vt();M("ytidb_create_logger_embed_killswitch")||hk();M("flush_gel_on_teardown")&&(a={},Qt||(Qt=new Pt),Qt.install((a.flush_logs={ka:function(){Vo()}},a)));
M("networkless_logging_web_embedded")&&(M("embeds_web_enable_new_nwl")?Sm():$m());M("embeds_enable_ua_ch_polyfill")&&Yt();M("ytidb_clear_embedded_player")&&bf.N(function(){var e;if(!Es){Kq||(Kq=new Hq);var f=Kq;var g={fc:Ds,Jb:Cs};f.providers.set(g.fc,g);g={ob:{feedbackEndpoint:Vq(ys),modifyChannelNotificationPreferenceEndpoint:Vq(zs),playlistEditEndpoint:Vq(As),subscribeEndpoint:Vq(ws),unsubscribeEndpoint:Vq(xs),webPlayerShareEntityServiceEndpoint:Vq(Bs)}};var h=M("web_enable_client_location_service")?
Rq.getInstance():void 0,k={};h&&(k.client_location=h);if(void 0===m){Bq.h||(Bq.h=new Bq);var m=Bq.h}void 0===e&&(e=f.resolve(Ds));ls(g,e,m,k);Es=ks.h}et()})});
var Yu=ei(function(){cs();var a=pj.getInstance(),b=sj(119),c=1<window.devicePixelRatio;if(document.body&&Bf(document.body,"exp-invert-logo"))if(c&&!Bf(document.body,"inverted-hdpi")){var d=document.body;if(d.classList)d.classList.add("inverted-hdpi");else if(!Bf(d,"inverted-hdpi")){var e=zf(d);Af(d,e+(0<e.length?" inverted-hdpi":"inverted-hdpi"))}}else!c&&Bf(document.body,"inverted-hdpi")&&Cf();if(b!=c){b="f"+(Math.floor(119/31)+1);d=tj(b)||0;d=c?d|67108864:d&-67108865;0==d?delete oj[b]:(c=d.toString(16),
oj[b]=c.toString());c=!0;M("web_secure_pref_cookie_killswitch")&&(c=!1);b=a.h;d=[];for(var f in oj)d.push(f+"="+encodeURIComponent(String(oj[f])));lj(b,d.join("&"),63072E3,a.i,c)}Os.h||(Os.h=new Os);a=Os.h;f=16623;var g=void 0===g?{}:g;Object.values(kq).includes(f)||(Np(new Q("createClientScreen() called with a non-page VE",f)),f=83769);g.isHistoryNavigation||a.h.push({rootVe:f,key:g.key||""});a.o=[];a.C=[];g.rb?Rs(a,f,g):Ss(a,f,g)}),Zu=ei(function(){Su&&Su.sendAbandonmentPing&&Su.sendAbandonmentPing();
A("PL_ATT")&&Et.dispose();for(var a=bf,b=0,c=tt.length;b<c;b++)a.U(tt[b]);tt.length=0;rt("//static.doubleclick.net/instream/ad_status.js");ut=!1;Xh("DCLKSTAT",0);qe(Uu,Tu);Su&&(Su.removeEventListener("onVideoDataChange",Vu),Su.destroy())});
window.addEventListener?(window.addEventListener("load",Yu),M("embeds_web_enable_replace_unload_w_pagehide")?window.addEventListener("pagehide",Zu):window.addEventListener("unload",Zu)):window.attachEvent&&(window.attachEvent("onload",Yu),window.attachEvent("onunload",Zu));y("yt.abuse.player.botguardInitialized",z("yt.abuse.player.botguardInitialized")||Ft);y("yt.abuse.player.invokeBotguard",z("yt.abuse.player.invokeBotguard")||Gt);
y("yt.abuse.dclkstatus.checkDclkStatus",z("yt.abuse.dclkstatus.checkDclkStatus")||wt);y("yt.player.exports.navigate",z("yt.player.exports.navigate")||Xu);y("yt.util.activity.init",z("yt.util.activity.init")||En);y("yt.util.activity.getTimeSinceActive",z("yt.util.activity.getTimeSinceActive")||Hn);y("yt.util.activity.setTimestamp",z("yt.util.activity.setTimestamp")||Fn);}).call(this);
