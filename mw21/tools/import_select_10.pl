#!/usr/bin/perl

# Copyright (C) 2017-2025 Marek Momot
#
# This file is part of MW21.
#
# MW21 is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# MW21 is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with MW21.  If not, see <http://www.gnu.org/licenses/>.

die "Usage: $0 absolute_src_dir absolute_dest_dir offset <list_of_10_files_from_here>\n" if @ARGV < 13;

my $offset = 0;

$src_dir = "@ARGV[0]";
$dest_dir = "@ARGV[1]";
$offset = "@ARGV[2]";

print "LINKING FILES:\n";
print "FROM: $src_dir\n";
print "TO: $dest_dir\n";
print "OFFSET: $offset\n";

my %names;

for($i = 0; $i < 10; $i++) {
    $prefix = sprintf("%04d", $i + $offset);
    $link_name = $prefix . "_" . cleanName(@ARGV[$i+3]);
    print "-------------------------------\n";
    print $src_dir . @ARGV[$i+3] . "\n";
    print $dest_dir . $link_name . "\n";
    symlink($src_dir . @ARGV[$i+3] , $dest_dir . $link_name);
}

sub cleanName {
    chomp $_[0];
    $old_name = "$_[0]";
    $new_name = "$_[0]";

    $new_name =~ s/Ą/A/g;
    $new_name =~ s/Ć/C/g;
    $new_name =~ s/Ę/E/g;
    $new_name =~ s/Ł/L/g;
    $new_name =~ s/Ń/N/g;
    $new_name =~ s/Ó/O/g;
    $new_name =~ s/Ś/S/g;
    $new_name =~ s/Ź/Z/g;
    $new_name =~ s/Ż/Z/g;

    $new_name =~ s/ą/a/g;
    $new_name =~ s/ć/c/g;
    $new_name =~ s/ę/e/g;
    $new_name =~ s/ł/l/g;
    $new_name =~ s/ń/n/g;
    $new_name =~ s/ó/o/g;
    $new_name =~ s/ś/s/g;
    $new_name =~ s/ź/z/g;
    $new_name =~ s/ż/z/g;

    $new_name =~ s/[^[:ascii:]]//g;
    $new_name =~ s/ /_/g;
    $new_name =~ s/[^A-Za-z0-9_.]//g;

    return $new_name;
}

sub link_item {
    $l_src_path = "$_[0]";
    $l_src_cleaned_filename = "$_[1]";
    $l_dst_dir = "$_[2]";
    $l_index = "$_[3]";

    $l_remove = "rm $l_dst_dir/$l_index*";

    system($l_remove);

    print "------------------------------------------\nLINKING\n";
    print "Absolute path is $l_src_path\n";
    print "Relative path is $l_src_cleaned_filename\n";
    $new_path = $l_dst_dir . $l_index . "_" . $l_src_cleaned_filename;
    print "$new_path\n";
    symlink($l_src_path, $new_path);
}
