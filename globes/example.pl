#! /usr/bin/perl -w
use lib "/usr/local/lib/globes/perl";
use globes;

print "\n\nPerl testing facility of GLoBES\n\n";
globes::glbInit("example.pl");
globes::PInit("NuFact1.glb");
$true_values=globes::glbAllocParams();
globes::glbDefineParams($true_values,0.1,0.2,0.3,0.4,0.5,0.6);
globes::glbSetOscillationParameters($true_values);
globes::glbSetRates();
$fit_values=globes::glbAllocParams();
globes::glbDefineParams($fit_values,0.1,0.2,0.4,0.4,0.5,0.6);
$chi=globes::glbChiSys($fit_values,$globes::GLB_ALL,$globes::GLB_ALL);
print "\nThis is the fit chi^2 value: $chi\n";
print "The Perl extension seems to be working ...\n";
print "bye bye\n"
