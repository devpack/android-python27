
all:
	@(cd sipgen; $(MAKE))
	@(cd siplib; $(MAKE))

install:
	@(cd sipgen; $(MAKE) install)
	@(cd siplib; $(MAKE) install)
	@test -d $(DESTDIR)/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/extras/python/site-packages || mkdir -p $(DESTDIR)/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/extras/python/site-packages
	cp -f sipconfig.py $(DESTDIR)/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/extras/python/site-packages/sipconfig.py
	cp -f /home/tsheasha/GUC/Bachelors/android-python27/python-build/sip-4.11.2/sipdistutils.py $(DESTDIR)/home/tsheasha/GUC/Bachelors/android-python27/python-build/output/extras/python/site-packages/sipdistutils.py

clean:
	@(cd sipgen; $(MAKE) clean)
	@(cd siplib; $(MAKE) clean)
