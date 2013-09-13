default: build

build:
	jekyll build -s ./site -d ./site/_site

deploy:
	ssh cs184-da@star.cs.berkeley.edu '~/cs184/deploy.sh'
