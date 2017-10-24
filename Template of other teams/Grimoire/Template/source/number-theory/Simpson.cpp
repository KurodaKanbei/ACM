// 三次函数，两倍精度拟合
// $error = \frac{(r - l)^5}{6480}|f^{(4)}|$
// $\int_{a}^{b} f(x) \, dx \approx \frac{(b-a)}{8}\left[f(a) + 3f\left(\frac{2a+b}{3}\right) + 3f\left(\frac{a+2b}{3}\right) + f(b)\right]\, $
// 三次函数拟合 $error = \frac{1}{90}{\frac{(r-l)}{2}}^5|f^{(4)}|$
d simpson(d fl,d fr,d fmid,d l,d r) {
	return (fl+fr+4.0*fmid)*(r-l)/6.0; }
d rsimpson(d slr,d fl,d fr,d fmid,d l,d r) {
	d mid = (l+r)/2,fml = f((l+mid)/2),fmr = f((mid+r)/2);
	d slm = simpson(fl,fmid,fml,l,mid);
	d smr = simpson(fmid,fr,fmr,mid,r);
	if(fabs(slr - smr - slm) / slr < eps)return slm + smr;
	return rsimpson(slm,fl,fmid,fml,l,mid)+
		rsimpson(smr,fmid,fr,fmr,mid,r);
}
