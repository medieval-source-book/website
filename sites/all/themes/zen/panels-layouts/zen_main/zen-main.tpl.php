<div class="layout-center">

  <?php if ($content['header']): ?>
    <header class="header" role="banner">
      <?php print $content['header']; ?>
    </header>
  <?php endif; ?>

  <div class="layout-3col  <?php if ($content['navigation']) print 'layout-swap'; ?>">

    <?php
      // Decide on layout classes by checking if sidebars have content.
      $content_class = 'layout-3col__full';
      $sidebar_first_class = $sidebar_second_class = '';
      if ($content['sidebar_first'] && $content['sidebar_second']):
        $content_class = 'layout-3col__right-content';
        $sidebar_first_class = 'layout-3col__first-left-sidebar';
        $sidebar_second_class = 'layout-3col__second-left-sidebar';
      elseif ($content['sidebar_second']):
        $content_class = 'layout-3col__left-content';
        $sidebar_second_class = 'layout-3col__right-sidebar';
      elseif ($content['sidebar_first']):
        $content_class = 'layout-3col__right-content';
        $sidebar_first_class = 'layout-3col__left-sidebar';
      endif;
    ?>

    <main class="<?php print $content_class; ?>" role="main">
      <?php print $content['highlighted']; ?>
      <a href="#skip-link" class="visually-hidden visually-hidden--focusable" id="main-content">Back to top</a>
      <?php print $content['content']; ?>
    </main>

    <?php if ($content['navigation']): ?>
      <div class="layout-swap__top layout-3col__full">
        <?php print $content['navigation']; ?>
      </div>
    <?php endif; ?>

    <?php if ($content['sidebar_first']): ?>
      <aside class="<?php print $sidebar_first_class; ?>" role="complementary">
        <?php print $content['sidebar_first']; ?>
      </aside>
    <?php endif; ?>

    <?php if ($content['sidebar_second']): ?>
      <aside class="<?php print $sidebar_second_class; ?>" role="complementary">
        <?php print $content['sidebar_second']; ?>
      </aside>
    <?php endif; ?>

  </div>

  <?php if ($content['footer']): ?>
    <footer class="footer" role="contentinfo">
      <?php print $content['header']; ?>
    </header>
  <?php endif; ?>

</div>
